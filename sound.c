#include <tamtypes.h>
#include <kernel.h>
#include <audsrv.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "sound.h"
#include "utils.h"

static FILE *music_file = NULL;
static int playing = 0;

static int read_thread_id = -1;
static volatile int read_thread_running = 0;

static u8 *ring_buffer = NULL;
static volatile size_t ring_write_pos = 0;  // where to write next
static volatile size_t ring_read_pos = 0;   // where to read from for audsrv
static volatile size_t ring_available = 0;  // how many bytes ready in ring

static void *ring_buffer_stack = NULL;

static void read_thread_func(void *arg) {
    (void)arg;

    u8 buf[8192];  // read chunk size

    while (read_thread_running) {
        if (ring_available < AUDIO_RING_SIZE) {  // room to write
            int read = fread(buf, 1, sizeof(buf), music_file);
            if (read <= 0) {
                read_thread_running = 0;
                break;
            }

            // Write to ring
            size_t space = AUDIO_RING_SIZE - ring_available;
            size_t to_write = read < space ? read : space;

            for (size_t i = 0; i < to_write; i++) {
                ring_buffer[ring_write_pos] = buf[i];
                ring_write_pos = (ring_write_pos + 1) % AUDIO_RING_SIZE;
            }

            ring_available += to_write;

            if (to_write < read) {
                // ring full — wait a bit
                SleepThread();
            }
        } else {
            // ring full — wait
            SleepThread();
        }
    }

    ExitDeleteThread();
}

void sound_init(void) {
    if (audsrv_init() < 0) return;

    // Allocate ring buffer
    ring_buffer = malloc(AUDIO_RING_SIZE);
    if (!ring_buffer) return;

    // Allocate stack for read thread
    ring_buffer_stack = malloc(0x2000);  // 8kB
}

void sound_stream_start(const char *filepath) {
    sound_stream_stop();

    if (!DEV_EXIST(filepath)) return;

    struct audsrv_fmt_t fmt = {0};
    fmt.bits = 16;
    fmt.freq = 48000;
    fmt.channels = 2;

    if (audsrv_set_format(&fmt) < 0) return;
    audsrv_set_volume(0x3fff);

    music_file = fopen(filepath, "rb");
    if (!music_file) return;

    ring_write_pos = 0;
    ring_read_pos = 0;
    ring_available = 0;

    // Start read thread
    ee_thread_t t;
    memset(&t, 0, sizeof(t));
    t.func = read_thread_func;
    t.stack = ring_buffer_stack;
    t.stack_size = 0x2000;
    t.gp_reg = &_gp;
    t.initial_priority = 0x50;  // lower than main
    t.attr = 0;
    t.option = 0;

    read_thread_id = CreateThread(&t);
    if (read_thread_id < 0) return;

    read_thread_running = 1;
    StartThread(read_thread_id, NULL);

    playing = 1;
}

void sound_stream_update(void) {
    if (!playing) return;

    if (ring_available == 0 && !read_thread_running) {
        sound_stream_stop();
        return;
    }

    // Feed small amount to audsrv per frame
    const int FEED_SIZE = 4096;  // small for smooth

    if (ring_available >= FEED_SIZE && audsrv_queued() < 16384) {
        u8 chunk[FEED_SIZE];

        for (int i = 0; i < FEED_SIZE; i++) {
            chunk[i] = ring_buffer[ring_read_pos];
            ring_read_pos = (ring_read_pos + 1) % AUDIO_RING_SIZE;
        }

        ring_available -= FEED_SIZE;

        audsrv_wait_audio(FEED_SIZE);
        audsrv_play_audio(chunk, FEED_SIZE);
    }
}

void sound_stream_stop(void) {
    if (!playing) return;

    read_thread_running = 0;
    if (read_thread_id >= 0) {
        TerminateThread(read_thread_id);
        DeleteThread(read_thread_id);
    }

    int timeout = 1000;
    while (audsrv_queued() > 0 && timeout--) {
        // SleepThread();
    }

    audsrv_stop_audio();

    if (music_file) {
        fclose(music_file);
        music_file = NULL;
    }

    playing = 0;
}
