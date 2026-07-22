#include <tamtypes.h>
#include <libpad.h>
#include <kernel.h>
#include <sifrpc.h>
#include <audsrv.h>
#include <iopcontrol.h>
#include <loadfile.h>
#include <libcdvd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sbv_patches.h>
#include <gsKit.h>
#include <libpad.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/stat.h>

#define NEWLIB_PORT_AWARE
#include <fileXio_rpc.h>
#include <io_common.h>

#define LOADER_BASE         0x01F00000
#define WORKPATH_ADDRESS    0x01EFFC00
#define PORTABLE_ADDRESS    0x01EFF800

#define SHARED_BASE_ADDR    0x01EFF7F0

#define INTERLACED          (SHARED_BASE_ADDR + 0x00)
#define PAL_NTSC            (SHARED_BASE_ADDR + 0x01)
#define PRIM_ALPHA          (SHARED_BASE_ADDR + 0x02)
#define HAS_TO_BE_TRUE      (SHARED_BASE_ADDR + 0x03)
#define GS_WIDTH            (SHARED_BASE_ADDR + 0x04)
#define GS_HEIGHT           (SHARED_BASE_ADDR + 0x08)
#define SIGNATURE_SPACE     (SHARED_BASE_ADDR + 0x0C)
#define SIGNATURE           0x4741597E

#define DEV_EXIST(path) (stat(path, &(struct stat){0}) == 0)

#define GS_BGCOLOR ((volatile u64*)0x120000e0)

void FuckAroundSilentlyMs(int miliseconds)
{
    unsigned int start, now;

    __asm__ volatile("mfc0 %0, $9" : "=r"(start));

    while (1)
    {
        __asm__ volatile("mfc0 %0, $9" : "=r"(now));
        if ((now - start) >= (unsigned int)(miliseconds * 147456))
            break;
    }
}
int main(int argc, char **argv)
{
    const char *argv0 = (argc > 0 && argv[0] != NULL) ? argv[0] : "(null)";

    strncpy((char*)PORTABLE_ADDRESS, argv0, 1023);
    ((char*)PORTABLE_ADDRESS)[1023] = '\0';

    *GS_BGCOLOR = 0x00FF00; // green - argv0 dumped, safe to inspect
    FuckAroundSilentlyMs(15000);
    while(1) {}
}
