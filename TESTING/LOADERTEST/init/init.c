#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <iopcontrol.h>
#include <loadfile.h>
#include <libcdvd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sbv_patches.h>
#include "gfx.h"
#include "audio.h"
#include "irx.h"
#include "pad.h"
#include "utils.h"
#include "handoff.h"

void init()
{
    SifInitRpc(0);
    while (!SifIopReset("", 0)) {};
    while (!SifIopSync()) {};
    SifInitRpc(0);
    SifLoadFileInit();
    sbv_patch_enable_lmb();

    // sound
    SifExecModuleBuffer(irx_freesd, irx_freesd_size, 0, NULL, NULL);
    SifExecModuleBuffer(irx_audsrv, irx_audsrv_size, 0, NULL, NULL);

    // controller
    SifLoadModule("rom0:SIO2MAN", 0, NULL);
    SifLoadModule("rom0:PADMAN", 0, NULL);
    pad_init();

    // memory card
    SifLoadModule("rom0:MCMAN", 0, NULL);
    SifLoadModule("rom0:MCSERV", 0, NULL);

    // USB I/O
    SifExecModuleBuffer(irx_iomanx, irx_iomanx_size, 0, NULL, NULL);
    SifExecModuleBuffer(irx_filexio, irx_filexio_size, 0, NULL, NULL);

    // USB Mass
    SifExecModuleBuffer(irx_usbd, irx_usbd_size, 0, NULL, NULL);
    SifExecModuleBuffer(irx_usbhdfsd, irx_usbhdfsd_size, 0, NULL, NULL);

    FuckAroundSilentlyMs(2000);

    // graphics — this is the ONLY ELF that ever calls the cold path
    gfx_init_cold();
    audio_init();

    HandoffInfo *h = handoff();
    h->magic     = HANDOFF_MAGIC;
    h->iop_ready = 1;

    h->gs_ready    = 1;
    h->Mode        = gsGlobal->Mode;
    h->Interlace   = gsGlobal->Interlace;
    h->Field       = gsGlobal->Field;
    h->Width       = gsGlobal->Width;
    h->Height      = gsGlobal->Height;
    h->PSM         = gsGlobal->PSM;
    h->FrameBuffer = gsGlobal->FrameBuffer;
    h->vram_watermark = gsGlobal->CurrentPointer;
}

int main(void)
{
    init();

    HandoffInfo *h = handoff();
    strcpy(h->path, "host:/MAIN.ELF");   // first ELF to hand control to

    // jump into the loader, which is resident at its fixed address —
    // SifLoadElf placed it there before this point (see note below)
    t_ExecData exec;
    if (SifLoadElf("host:/LOADER.ELF", &exec) != 0) {
        while (1) {}   // no loader, nothing to do
    }

    SifExitRpc();
    char *argv[1] = { h->path };
    ExecPS2((void*)exec.epc, (void*)exec.gp, 1, argv);

    return 0; // never reached
}
