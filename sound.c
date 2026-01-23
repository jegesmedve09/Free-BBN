#include <tamtypes.h>
#include <kernel.h>
#include <audsrv.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>     // Added for memset

#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <iopcontrol.h>
#include <loadfile.h>
#include <audsrv.h>
#include <stdio.h>
#include <malloc.h>

#include "gfx.h"
#include "utils.h"

#define SAMPLE_RATE 48000
#define CHANNELS 2
#define CHUNK_SIZE (32 * 1024)

static int sound_running = 0;

static int sound_thread(void *arg) {
    const char* file_path = (const char*)arg;
    FILE* fd = fopen(file_path, "rb");
    if (!fd) {
        sound_running = 0;
        ExitDeleteThread();
        return 0;
    }

    struct audsrv_fmt_t format = {16, SAMPLE_RATE, CHANNELS};
    audsrv_set_format(&format);
    audsrv_set_volume(MAX_VOLUME);

    char* buffer = (char*)memalign(64, CHUNK_SIZE);
    if (!buffer) {
        fclose(fd);
        sound_running = 0;
        ExitDeleteThread();
        return 0;
    }

    while (1) {
        int bytes = fread(buffer, 1, CHUNK_SIZE, fd);
        if (bytes <= 0) break;

        // Non-blocking check for space in audsrv ring buffer
        while (audsrv_available() < bytes) {
            // Short busy-wait yield (~few us per call) instead of DelayThread
            // Tune loop count: 1000–5000 ≈ 0.5–2 ms on real PS2 (test!)
            volatile int i;
            for (i = 0; i < 3000; i++) {
                nopdelay();     // NOP + cache flush hint; very lightweight
            }
        }
        audsrv_play_audio(buffer, bytes);
    }

    free(buffer);
    fclose(fd);

    // Drain remaining queued audio
    while (audsrv_queued() > 0) {
        volatile int i;
        for (i = 0; i < 10000; i++) {   // Longer drain wait
            nopdelay();
        }
    }

    sound_running = 0;
    ExitDeleteThread();
    return 0;
}

void sound_init(void) {
    printf("Entering sound_init\n");  // If you have serial/ps2link printf
    gfx_draw_text("Inside sound_init", 40, 100, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0), 8, 2);
    gfx_flip(); gfx_exec();
    audsrv_init();
    gfx_draw_text("audsrv_init RETURNED!", 40, 140, GS_SETREG_RGBAQ(0x00,0xFF,0x00,0x80,0), 8, 2);
    gfx_flip(); gfx_exec();
}

void sound_play_async(const char* file_path) {
    if (sound_running) return;

    sound_running = 1;
    ee_thread_t th;
    memset(&th, 0, sizeof(ee_thread_t));

    th.func = sound_thread;
    th.stack = memalign(16, 8192);
    th.stack_size = 8192;
    th.gp_reg = &_gp;
    th.initial_priority = 60;       // Lower prio than main (adjust if starving)
    th.attr = 0;
    th.option = 0;

    int tid = CreateThread(&th);
    if (tid < 0) {
        sound_running = 0;
        free(th.stack);
        return;
    }

    StartThread(tid, (void*)file_path);
}
