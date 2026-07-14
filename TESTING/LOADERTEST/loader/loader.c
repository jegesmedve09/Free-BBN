#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <sbv_patches.h>
#include "handoff.h"

int main(int argc, char *argv[])
{
    // RPC/IOP already up from INIT — don't touch it, just make sure
    // this ELF's own SIF bindings are valid.
    SifInitRpc(0);
    SifLoadFileInit();
    sbv_patch_enable_lmb();

    HandoffInfo *h = handoff();

    if (h->magic != HANDOFF_MAGIC) {
        // Should never happen — INIT always sets this before first jump.
        // Nothing sane to do but halt.
        while (1) {}
    }

    t_ExecData exec;
    int ret = SifLoadElf(h->path, &exec);
    if (ret != 0) {
        // TODO: once you have a font/screen fallback that doesn't depend on
        // fresh GS init, draw an error here. For now, just halt so it's obvious.
        while (1) {}
    }

    SifExitRpc();

    char *elf_argv[1] = { h->path };
    ExecPS2((void*)exec.epc, (void*)exec.gp, 1, elf_argv);

    // never reached
    return 0;
}
