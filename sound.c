#include <tamtypes.h>
#include <audsrv.h>
#include <stdio.h>
#include <malloc.h>
#include "utils.h"

#define SAMPLE_RATE 48000
#define CHANNELS 2
#define CHUNK_SIZE 4096*2

static FILE* sound_fd = NULL;
static char* buffer = NULL;
static int sound_active = 0;

void sound_init(void)
{
    audsrv_init();
}

int sound_start(const char* file_path)
{
    //if (sound_active) return;
    
    sound_fd = fopen(file_path, "rb");
    if (!sound_fd) return 1;

    struct audsrv_fmt_t format = {16, SAMPLE_RATE, CHANNELS};
    audsrv_set_format(&format);
    audsrv_set_volume(MAX_VOLUME);

    buffer = memalign(64, CHUNK_SIZE);
    if (!buffer) {
        fclose(sound_fd);
        sound_fd = NULL;
        sound_active =0;
        return 0;
    }

    sound_active = 1;
}

int sound_update(void)
{
    if (!sound_active || !sound_fd) return 0;

    if (sizeof(buffer) < 100) {
        //FlushCache(0);
		int bytes = fread(buffer, 1, CHUNK_SIZE, sound_fd);
        audsrv_wait_audio(bytes);
        audsrv_play_audio(buffer, bytes);
        return 1;  // Still playing
    }

    // End of file
    audsrv_wait_audio(0);
    free(buffer);
    fclose(sound_fd);
    sound_fd = NULL;
    buffer = NULL;
    sound_active = 0;

    return 0;  // Finished
}

int sound_stop(void)
{
    audsrv_wait_audio(0);
    free(buffer);
    fclose(sound_fd);
    sound_fd = NULL;
    buffer = NULL;
    sound_active = 0;

    return 0;  // Finished
}
