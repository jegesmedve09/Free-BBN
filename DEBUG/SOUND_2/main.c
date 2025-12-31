#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <audsrv.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define STREAM_BUF 4096
#define AUDIO_PATH "host:music.raw"

int main(int argc, char *argv[])
{
    int fd;
    static char buffer[STREAM_BUF];
    struct audsrv_fmt_t fmt;

    SifInitRpc(0);

    if (audsrv_init() != 0) {
        printf("audsrv init failed\n");
        return 1;
    }

    fmt.freq = 48000;
    fmt.bits = 16;
    fmt.channels = 2;

    audsrv_set_format(&fmt);
    audsrv_set_volume(0x3fff);

    fd = open(AUDIO_PATH, O_RDONLY);
    if (fd < 0) {
        printf("Failed to open audio file\n");
        return 1;
    }

    while (1) {
        int bytes = read(fd, buffer, STREAM_BUF);
        if (bytes <= 0)
            break;

        audsrv_wait_audio(bytes);
        audsrv_play_audio(buffer, bytes);
    }

    close(fd);

    // Let remaining audio drain
    audsrv_wait_audio(0);
    sleep(1);

    audsrv_quit();
    return 0;
}

