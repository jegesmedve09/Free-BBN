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

#define AUDIO_RING_SIZE (131072)

// Helper to write to circular buffer (efficient memcpy)
static void ring_write(const u8 *src, size_t len) {
    if (len == 0) return;
    size_t space_to_end = AUDIO_RING_SIZE - ring_write_pos;
    if (len <= space_to_end) {
        memcpy(ring_buffer + ring_write_pos, src, len);
        ring_write_pos += len;
    } else {
        memcpy(ring_buffer + ring_write_pos, src, space_to_end);
        memcpy(ring_buffer, src + space_to_end, len - space_to_end);
        ring_write_pos = len - space_to_end;
    }
    ring_available += len;
}

// Helper to read from circular buffer
static void ring_read(u8 *dest, size_t len) {
    if (len == 0) return;
    size_t space_to_end = AUDIO_RING_SIZE - ring_read_pos;
    if (len <= space_to_end) {
        memcpy(dest, ring_buffer + ring_read_pos, len);
        ring_read_pos += len;
    } else {
        memcpy(dest, ring_buffer + ring_read_pos, space_to_end);
        memcpy(dest + space_to_end, ring_buffer, len - space_to_end);
        ring_read_pos = len - space_to_end;
    }
    ring_available -= len;
}


static void read_thread_func(void *arg) {
    (void)arg;
    u8 buf[16384];  // Larger chunk for fewer syscalls
    while (read_thread_running) {
        size_t space = AUDIO_RING_SIZE - ring_available;
        if (space == 0) {
            SleepThread();
            continue;
        }
        size_t want_read = (space < sizeof(buf)) ? space : sizeof(buf);
        int read = fread(buf, 1, want_read, music_file);
        if (read <= 0) {
            read_thread_running = 0;
            break;
        }
        ring_write(buf, read);
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

    int free = audsrv_available();  // Free bytes in IOP buffer
    if (free <= 0) return;

    size_t to_feed = (ring_available < (size_t)free) ? ring_available : (size_t)free;
    const size_t MAX_CHUNK = 8192;  // Tune: larger = smoother, but more bursty
    if (to_feed > MAX_CHUNK) to_feed = MAX_CHUNK;

    u8 chunk[MAX_CHUNK];
    ring_read(chunk, to_feed);

    audsrv_play_audio((char *)chunk, to_feed);  // No wait_audio - we checked!

    WakeupThread(read_thread_id);  // Wake reader if it was sleeping
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
