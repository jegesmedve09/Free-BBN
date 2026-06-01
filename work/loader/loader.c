#include <tamtypes.h>
#include <kernel.h>
#include <loadfile.h>
#include <sifrpc.h>
#include <string.h>

#define WORKPATH_ADDR  0x01EFFC00

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
    strncpy(fullpath, workpath, 400);
    fullpath[400] = '\0';
    strncat(fullpath, argv[0], 111);
    fullpath[511] = '\0';

    ret = SifLoadElf(fullpath, &exec);
    if (ret < 0)
        return -1;

    FlushCache(0);
    FlushCache(2);

    ExecPS2((void *)exec.epc, (void *)exec.gp, argc, argv);

    return -1;
}

void _exit(int code) { (void)code; for (;;); }
