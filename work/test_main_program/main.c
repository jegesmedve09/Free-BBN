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

#include <sys/stat.h>

GSGLOBAL *gsGlobal;

// In your main.elf — call this instead of a full init
void ReconnectIOP(void)
{
    // Re-establish EE<->IOP link WITHOUT resetting IOP
    // (modules are already loaded and running on IOP side)
    SifInitRpc(0);
    SifLoadFileInit();   // re-register EE-side load file client

    // Re-init EE-side pad client (IOP PADMAN is still running)
    padInit(0);

    // Re-init EE-side audsrv client (IOP audsrv is still running)
    audsrv_init();

    // gsKit is 100% EE/GS hardware — just re-init it normally
    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
                D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

    gsGlobal = gsKit_init_global();
    // ... set your mode/width/height etc. as normal
    gsKit_init_screen(gsGlobal);
}



int main()
{
	
	ReconnectIOP();
	
	while (1) {	gsKit_clear(gsGlobal, GS_SETREG_RGBAQ(0,0,0xFF,80,0));
	gsKit_queue_exec(gsGlobal);
	gsKit_sync_flip(gsGlobal);}
}
