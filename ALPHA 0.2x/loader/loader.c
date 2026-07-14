#include <tamtypes.h>
#include <kernel.h>
#include <loadfile.h>
#include <sifrpc.h>
#include <string.h>

#define WORKPATH_ADDR  0x01EFFC00
#define DEBUG_MARKER ((volatile unsigned char*)0x01EFFB00)

#define DEBUG_MARKER  ((volatile unsigned char*)0x01EFFB00)
#define DEBUG_RETCODE ((volatile int*)0x01EFFB04)
#define DEBUG_PATHBUF ((volatile char*)0x01EFFB10) 

#define DEBUG_ARGV0PTR  ((volatile unsigned int*)0x01EFFB20)
#define DEBUG_ARGV0BYTE ((volatile unsigned char*)0x01EFFB24)
#define RELPATH_ADDR 0x01EFFA00

//extern void _ps2sdk_memory_init(void);
extern void _InitSys(void);

int main(int argc, char **argv)
{
    *DEBUG_MARKER = 0x22;
*DEBUG_ARGV0PTR = (unsigned int)argv[0];
*DEBUG_ARGV0BYTE = argv[0] ? *(unsigned char*)argv[0] : 0xFF;
    //_ps2sdk_memory_init();
    _InitSys();
    t_ExecData exec;
    char fullpath[512];
    char *workpath = (char *)WORKPATH_ADDR;
    int ret;

    // MUST reinitialize — BSS clear zeroed all SIF/RPC client state
    SifInitRpc(0);
    SifLoadFileInit();

    //if (argc < 1 || !argv[0] || !argv[0][0])
        //return -1;
    *DEBUG_MARKER = 0x33;
    //if (argc < 1) return -1;
    //if (argv == NULL) { /* loop forever so we can see we got this far */    while(1){} }
    //if (!argv[0] || !argv[0][0]) return -1;    

    // Build full path: WORKPATH + relative path
char *relpath = (char*)RELPATH_ADDR;

if (!relpath[0])
    return -1;

strncpy(fullpath, workpath, 400);
fullpath[400] = '\0';
strncat(fullpath, relpath, 111);
fullpath[511] = '\0';

    strcpy((char*)DEBUG_PATHBUF, fullpath);   // snapshot exactly what we're about to hand SifLoadElf

    *DEBUG_MARKER = 0x44;
    ret = SifLoadElf(fullpath, &exec);
    *DEBUG_RETCODE = ret;
    *DEBUG_MARKER = 0x45;
    if (ret < 0)
        return -1;
    *DEBUG_MARKER = 0x46;

    FlushCache(0);
    FlushCache(2);
    *DEBUG_MARKER = 0x55;
    ExecPS2((void *)exec.epc, (void *)exec.gp, 0, NULL);

    return -1;
}

void _exit(int code) { (void)code; for (;;); }
