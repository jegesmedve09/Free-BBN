#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <iopcontrol.h>
#include <loadfile.h>
#include <sbv_patches.h>

#include "gfx.h"
#include "audio.h"
#include "irx.h"
#include "pad.h"
#include "utils.h"

void init(void)
{
    SifInitRpc(0);
    while (!SifIopReset("", 0)) {};
    while (!SifIopSync()) {};
    SifInitRpc(0);
    SifLoadFileInit();
    sbv_patch_enable_lmb();

    SifExecModuleBuffer(irx_freesd, irx_freesd_size, 0, NULL, NULL);
    SifExecModuleBuffer(irx_audsrv, irx_audsrv_size, 0, NULL, NULL);

    //controller
    SifLoadModule("rom0:SIO2MAN", 0, NULL);
    SifLoadModule("rom0:PADMAN", 0, NULL);
    pad_init();
    
    //memory card
    SifLoadModule("rom0:MCMAN", 0, NULL);
    SifLoadModule("rom0:MCSERV", 0, NULL);
    
    //USB I/O
    SifExecModuleBuffer(irx_iomanx, irx_iomanx_size, 0, NULL, NULL);
    SifExecModuleBuffer(irx_filexio, irx_filexio_size, 0, NULL, NULL);
    
    //USB Mass
    SifExecModuleBuffer(irx_usbd, irx_usbd_size, 0, NULL, NULL);
    SifExecModuleBuffer(irx_usbhdfsd, irx_usbhdfsd_size, 0, NULL, NULL);
    
    
    FuckAroundSilentlyMs(2000);

    //graphics
    gfx_init();
    
    audio_init();

}

int main(void)
{
    init();
    gfx_clear(GS_SETREG_RGBAQ(255,255,255,80,0));
    gfx_flip();
    gfx_exec();
    
    while (1) {}
    return 0;

}
