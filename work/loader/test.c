#include <tamtypes.h>
#include <kernel.h>
#include <loadfile.h>

#define LOADER_BASE     0x01F00000
#define WORKPATH_ADDR   0x01EFFC00

char *WORKPATH = (char*)WORKPATH_ADDR;

int main(int argc, char **argv)
{
    char fullpath[512];

    FlushCache(0);

    // Build full path manually
    simple_strcpy(fullpath, WORKPATH);
    simple_strcat(fullpath, argv[0]);

    int ret = SifLoadElf(fullpath, &exec);
    if (ret < 0) {
        while(1);
    }

    FlushCache(0);
    FlushCache(2);

    ExecPS2((void*)exec.epc, (void*)exec.gp, 0, NULL);

    while(1);
    return -1;
}

void _exit(int code) { (void)code; while(1); }

