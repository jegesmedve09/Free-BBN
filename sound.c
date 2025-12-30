#include <tamtypes.h>
#include <audsrv.h>
#include <stdio.h>
#include <malloc.h>
#include <libsd.h>

#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <iopcontrol.h>
#include <loadfile.h>
#include <audsrv.h>
#include <stdio.h>
#include <malloc.h>

#define SAMPLE_RATE 48000
#define CHANNELS 1

void sound_init(void)
{
    audsrv_init();
}

void PlaySound(const char* file_path)
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
