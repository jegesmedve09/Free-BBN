#include <tamtypes.h>
#include <kernel.h>
#include <loadfile.h>
#include <sifrpc.h>
#include <string.h>

#define WORKPATH_ADDR  0x01FFFFF0

int main(int argc, char **argv)
{
    t_ExecData exec;
    char fullpath[512];
    char *workpath = (char *)WORKPATH_ADDR;
    int ret;

    // MUST reinitialize — BSS clear zeroed all SIF/RPC client state
    SifInitRpc(0);
    SifLoadFileInit();

    if (argc < 1 || !argv[0] || !argv[0][0])
        return -1;

    // Build full path: WORKPATH + relative path
    strncpy(fullpath, workpath, 16);
    fullpath[511] = '\0';
    strncat(fullpath, argv[0], 111);
    fullpath[511] = '\0';

    ret = SifLoadElf(fullpath, &exec);
    if (ret < 0)
        return -1;

    FlushCache(0);
    FlushCache(2);

    asm volatile (
        "move $a0, %0\n\t"   // Place argc into $a0
        "move $a1, %1\n\t"   // Place argv into $a1
        "move $gp, %2\n\t"   // Setup the new application's global pointer
        "jr   %3\n\t"        // Jump register straight to the Entry Point
        "nop\n\t"            // MIPS branch delay slot
        :
        : "r"(argc), "r"(argv), "r"(exec.gp), "r"(exec.epc)
        : "a0", "a1", "gp"
    );

    return -1;
}

void _exit(int code) { (void)code; for (;;); }
