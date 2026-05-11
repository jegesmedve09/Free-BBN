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


int main()
{
	
    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
                D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

    gsGlobal = gsKit_init_global();

    gsGlobal->Mode         = GS_MODE_PAL;
    gsGlobal->Interlace    = GS_INTERLACED;
    gsGlobal->Field        = GS_FIELD;
    gsGlobal->Width        = 640;
    gsGlobal->Height       = 512;
    gsGlobal->DoubleBuffering = GS_SETTING_OFF;
    gsGlobal->ZBuffering   = GS_SETTING_OFF;

    // === The important transparency settings ===
    gsGlobal->PrimAlphaEnable = GS_SETTING_ON;
    
    gsKit_init_screen(gsGlobal);

    // Normal "over" blending - most common and intuitive
    gsKit_set_primalpha(gsGlobal,
        GS_SETREG_ALPHA(0, 1, 0, 1, 0),   // A = As, B = 1-As
        0);

    gsKit_mode_switch(gsGlobal, GS_ONESHOT);
 
	gsKit_clear(gsGlobal, GS_SETREG_RGBAQ(0,0,0xFF,80,0));
	gsKit_queue_exec(gsGlobal);
	gsKit_sync_flip(gsGlobal);
	
	
	while (1) {}
}
