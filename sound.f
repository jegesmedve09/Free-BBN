#include <tamtypes.h>
#include <kernel.h>
#include <audsrv.h>
#include <stdio.h>
#include <malloc.h>
#include "utils.h"

#define SAMPLE_RATE 48000
#define CHANNELS 1
#define CHUNK_SIZE (32 * 1024)

static int sound_thread_id;
static int sound_running = 0;

int sound_thread(void *arg)
{
    const char* file_path = (const char*)arg;

    FILE* fd = fopen(file_path, "rb");
    if (!fd) {
        sound_running = 0;
        ExitThread();
        return 0;
    }

    struct audsrv_fmt_t format = {16, SAMPLE_RATE, CHANNELS};
    audsrv_set_format(&format);
    audsrv_set_volume(MAX_VOLUME);

    char* buffer = memalign(64, CHUNK_SIZE);
    if (!buffer) {
        fclose(fd);
        sound_running = 0;
        ExitThread();
        return 0;
    }

    while (1)
    {
        int bytes = fread(buffer, 1, CHUNK_SIZE, fd);
        if (bytes <= 0) break;

        while (audsrv_available() < (bytes / 2)) {
            DelayThread(1000);  // 1ms sleep — low CPU, lets graphics run
        }

        audsrv_play_audio(buffer, bytes);
    }

    free(buffer);
    fclose(fd);

    // Wait for last chunk to finish
    while (audsrv_queued() > 0) {
        DelayThread(10000);
    }

    sound_running = 0;
    ExitThread();
    return 0;
}

void sound_init(void)
{
    audsrv_init();
}

void PlaySoundAsync(const char* file_path)
{
    if (sound_running) return;  // Only one sound at a time

    sound_running = 1;

    // Create thread (stack 8KB, priority 32)
    struct ThreadParam param;
    param.entry = sound_thread;
    param.stack = memalign(128, 8192);
    param.stackSize = 8192;
    param.gpReg = (void*)_gp;
    param.priority = 32;
    param.initPriority = 32;

    sound_thread_id = CreateThread(&param);
    if (sound_thread_id < 0) {
        sound_running = 0;
        return;
    }

    StartThread(sound_thread_id, (void*)file_path);
}
