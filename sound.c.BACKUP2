
#include <tamtypes.h>
#include <audsrv.h>
#include <stdio.h>
#include <malloc.h>
#include <kernel.h>
#include "utils.h"

#define SAMPLE_RATE 48000
#define CHANNELS 2

#define STREAM_CHUNK 4096

static int sound_thread_id = -1;
static int sound_running = 0;

void sound_init(void)
{
    audsrv_init();
}

//void play_sound_function(const char* file_path)
void PlaySound(const char* file_path)
{
    FILE* fd = fopen(file_path, "rb");
    if (!fd) return;

    struct audsrv_fmt_t format;
    format.bits = 16;
    format.freq = SAMPLE_RATE;   // e.g. 48000
    format.channels = CHANNELS;  // 1 or 2

    audsrv_set_format(&format);
    audsrv_set_volume(MAX_VOLUME);

    char* buffer = memalign(64, STREAM_CHUNK);
    if (!buffer) {
        fclose(fd);
        return;
    }

    while (1)
    {
        int bytes = fread(buffer, 1, STREAM_CHUNK, fd);
        if (bytes <= 0)
            break;
            
        FlushCache(0);
        audsrv_wait_audio(bytes);        // 🔑 THIS IS REQUIRED
        audsrv_play_audio(buffer, bytes);
    }

    // drain remaining audio
    audsrv_wait_audio(0);

    free(buffer);
    fclose(fd);
}
