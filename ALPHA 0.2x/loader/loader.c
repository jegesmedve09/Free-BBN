#include <tamtypes.h>
#include <kernel.h>
#include <loadfile.h>
#include <iopcontrol.h>
#include <sifrpc.h>
#include <string.h>

#define GS_BASE 0x12000000
#define GS_BGCOLOR ((volatile u64*)0x120000e0)

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

extern void _InitSys(void);
extern int EIntr(void);
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
    _InitSys();
    EIntr();
    t_ExecData exec;
    char fullpath[2048];
    char *workpath = (char *)WORKPATH_ADDRESS;
    char *portablepath = (char *)PORTABLE_ADDRESS;
    int ret;

    SifInitRpc(0);
    SifLoadFileInit();
    
    //FuckAroundSilentlyMs(1000);    

    if (*(volatile u32*)SIGNATURE_SPACE != SIGNATURE)
    {
        *GS_BGCOLOR = 0xFF00FF;   // magenta = handoff never happened
        while(1) {}
    }    

    strncpy(fullpath, portablepath, sizeof(fullpath) - 1);
    fullpath[sizeof(fullpath) - 1] = '\0';

    strncat(fullpath, workpath, sizeof(fullpath) - strlen(fullpath) - 1);
    fullpath[sizeof(fullpath) - 1] = '\0';


    *GS_BGCOLOR = 0x00FF00;
    ret = SifLoadElf(fullpath, &exec);
    if (ret < 0)
    {
        *GS_BGCOLOR = 0xFF0000;   // red
    }
     else if (exec.epc == 0)
    {
        for (int i = 0; i < ret && i < 20; i++)
        {
            *GS_BGCOLOR = 0xFFFFFF;
            FuckAroundSilentlyMs(1000);
            *GS_BGCOLOR = 0x000000;
            FuckAroundSilentlyMs(1000);
        }
        FuckAroundSilentlyMs(1000);
        *GS_BGCOLOR = 0x00FFFF;
        while(1) {}
    }
    else
    {
        //FuckAroundSilentlyMs(3000);

        asm volatile("sync.l");
        FlushCache(0);
        FlushCache(2);
        static char *argv[] = {"FreeBBN", NULL};
        ExecPS2((void *)exec.epc, (void *)exec.gp, 1, argv);
    }
    return -1;
}

void _exit(int code) { (void)code; for (;;); }
