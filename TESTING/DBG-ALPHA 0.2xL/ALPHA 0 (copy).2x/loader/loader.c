#include <tamtypes.h>
#include <kernel.h>
#include <loadfile.h>
#include <iopcontrol.h>
#include <sifrpc.h>
#include <string.h>


#define GS_BASE 0x12000000

#define WORKPATH_ADDR  0x01EFFC00

#define GS_BGCOLOR ((volatile u64*)0x120000e0)   // if not already declared via kernel.h/gsKit.h

//extern void _ps2sdk_memory_init(void);
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
    //_ps2sdk_memory_init();
    _InitSys();
    EIntr();
    *GS_BGCOLOR = 0x0000FF;
    t_ExecData exec;
    char fullpath[512];
    char *workpath = (char *)WORKPATH_ADDR;
    int ret;

    // MUST reinitialize — BSS clear zeroed all SIF/RPC client state
    SifInitRpc(0);
    SifLoadFileInit();
    //while (!SifIopSync()) {};
    
    FuckAroundSilentlyMs(1000);    

    //if (argc < 1 || !argv[0] || !argv[0][0])
        //return -1;
    //if (argc < 1) return -1;
    //if (argv == NULL) { /* loop forever so we can see we got this far */    while(1){} }
    //if (!argv[0] || !argv[0][0]) return -1;    

    strncpy(fullpath, workpath, 400);
    fullpath[400] = '\0';


    *GS_BGCOLOR = 0x00FF00;
    ret = SifLoadElf(workpath, &exec);
    if (ret < 0)
    {
        *GS_BGCOLOR = 0xFF0000;   // red
    }
     else if (exec.epc == 0) {
    // flash white N times, where N = ret, so we can read the actual value
    for (int i = 0; i < ret && i < 20; i++) {
        *GS_BGCOLOR = 0xFFFFFF;
        FuckAroundSilentlyMs(400);
        *GS_BGCOLOR = 0x000000;
        FuckAroundSilentlyMs(400);
    }
    FuckAroundSilentlyMs(1000);
    *GS_BGCOLOR = 0x00FFFF;   // hold cyan afterward so you know the flashing is done
    while(1) {}
    }
    else
    {
        *GS_BGCOLOR = 0xFFFF00;   // yellow = epc/gp look genuinely valid
        FuckAroundSilentlyMs(3000);

        asm volatile("sync.l");
        FlushCache(0);
        FlushCache(2);
        static char *argv[] = {"FreeBBN", NULL};
        ExecPS2((void *)exec.epc, (void *)exec.gp, 1, argv);
    }
    return -1;
}

void _exit(int code) { (void)code; for (;;); }
