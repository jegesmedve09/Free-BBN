#include <tamtypes.h>
#include <audsrv.h>
#include <stdio.h>
#include <malloc.h>
#include "utils.h"

#define SAMPLE_RATE 48000
#define CHANNELS 2
#define CHUNK_SIZE 4096

static FILE* fd = NULL;
static char* buffer = NULL;
static int playing = 0;

void sound_init(void)
{
    audsrv_init();
}

void StartSound(const char* file_path)
{
    if (playing) return;

    fd = fopen(file_path, "rb");
    if (!fd) return;

    struct audsrv_fmt_t format = {16, SAMPLE_RATE, CHANNELS};
    audsrv_set_format(&format);
    audsrv_set_volume(MAX_VOLUME);

    buffer = memalign(64, CHUNK_SIZE);
    if (!buffer) {
        fclose(fd);
        fd = NULL;
        return;
    }

    playing = 1;
}

int UpdateSound(void)
{
    if (!playing) return 0;

    int bytes = fread(buffer, 1, CHUNK_SIZE, fd);
    if (bytes > 0) {
        audsrv_wait_audio(bytes);
        audsrv_play_audio(buffer, bytes);
        return 1;
    }

    audsrv_wait_audio(0);
    free(buffer);
    fclose(fd);
    buffer = NULL;
    fd = NULL;
    playing = 0;

    return 0;
}
