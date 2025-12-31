#include <tamtypes.h>
#include <kernel.h>
#include <audsrv.h>
#include <stdio.h>
#include <malloc.h>
#include <libsd.h>
#include "utils.h"


#define SAMPLE_RATE 48000
#define CHANNELS 1
#define BUFFER_SIZE (64 * 1024)  // 64 KB per buffer — 128 KB total


void sound_init(void)
{
    audsrv_init();
}

#define STREAM_CHUNK 4096

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

        audsrv_wait_audio(bytes);        // 🔑 THIS IS REQUIRED
        audsrv_play_audio(buffer, bytes);
    }

    // drain remaining audio
    audsrv_wait_audio(0);

    free(buffer);
    fclose(fd);
}

void PlaySound_working(const char* file_path)
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

        audsrv_wait_audio(bytes);        // 🔑 THIS IS REQUIRED
        audsrv_play_audio(buffer, bytes);
    }

    // drain remaining audio
    audsrv_wait_audio(0);

    free(buffer);
    fclose(fd);
}


void PlaySound_old(const char* file_path)
{
    FILE* fd = fopen(file_path, "rb");
    if (!fd) return;

    fseek(fd, 0, SEEK_END);
    long size = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    char* buffer = (char*)memalign(64, size);
    fread(buffer, 1, size, fd);    //if (!buffer) { //    fclose(fd);  //    return;  //}
    fclose(fd);


    fread(buffer, 1, size, fd);
    fclose(fd);

    struct audsrv_fmt_t format;
    format.bits = 16;
    format.freq = SAMPLE_RATE;
    format.channels = CHANNELS;
    audsrv_set_format(&format);
    audsrv_set_volume(MAX_VOLUME);

    audsrv_play_audio(buffer, size);//audsrv_ch_play_adpcm(-1, (audsrv_adpcm_t*)buffer);

    // Wait ~10 seconds (adjust for your sound length)
    volatile int i = 200000000;
    while (i--) {};

    free(buffer);
}
