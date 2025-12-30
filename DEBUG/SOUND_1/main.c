#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <iopcontrol.h>
#include <loadfile.h>
#include <audsrv.h>
#include <stdio.h>
#include <malloc.h>

#define SAMPLE_RATE 48000
#define CHANNELS    1
#define BITS        16

int main(void)
{
    int ret;
    FILE *fd;
    void *buffer;
    int size;

    SifInitRpc(0);

    /* HARD IOP RESET (MANDATORY) */
    while (!SifIopReset("", 0)) {}
    while (!SifIopSync()) {}

    SifInitRpc(0);
    SifLoadFileInit();

    /* Required sound driver */
    ret = SifLoadModule("rom0:LIBSD", 0, NULL);
    printf("LIBSD: %d\n", ret);

    /* Load audsrv */
    ret = SifLoadModule("host:audsrv.irx", 0, NULL);
    printf("AUDSRV: %d\n", ret);

    printf("Initializing audsrv...\n");
    audsrv_init();
    printf("audsrv OK\n");

    /* Open RAW PCM file */
    fd = fopen("host:sound/startup.raw", "rb");
    if (!fd) {
        printf("Failed to open audio file\n");
        SleepThread();
    }

    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    buffer = memalign(512, size);
    fread(buffer, 1, size, fd);
    fclose(fd);

    /* Set audio format */
    struct audsrv_fmt_t fmt;
    fmt.freq = SAMPLE_RATE;
    fmt.bits = BITS;
    fmt.channels = CHANNELS;

    audsrv_set_format(&fmt);
    audsrv_set_volume(MAX_VOLUME);

    printf("Playing audio (%d bytes)\n", size);

    /* Play PCM buffer */
    audsrv_play_audio(buffer, size);

    /* Wait until playback finishes */

    printf("Playback done\n");


    /* Idle forever */
    SleepThread();
    return 0;
}

