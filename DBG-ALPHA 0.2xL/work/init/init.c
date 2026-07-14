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

#include "irx.c"
#include "loader_bin.c"


GSGLOBAL *gsGlobal;

#define LOADER_BASE 0x01F00000
#define WORKPATH_ADDRESS 0x01EFFC00

#define DEV_EXIST(path) (stat(path, &(struct stat){0}) == 0)
#define DEBUG_MARKER ((volatile unsigned char*)0x01EFFB00)

#define RELPATH_ADDRESS 0x01EFFA00

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

int main()
{	
	SifInitRpc(0);
    while (!SifIopReset("", 0)) {};
    while (!SifIopSync()) {};
    SifInitRpc(0);
    SifLoadFileInit();
    sbv_patch_enable_lmb();
    
    //sound
    SifExecModuleBuffer(irx_libsd, irx_libsd_size, 0, NULL, NULL);
    SifExecModuleBuffer(irx_audsrv, irx_audsrv_size, 0, NULL, NULL);
    audsrv_init();
    
    //controller
    SifLoadModule("rom0:SIO2MAN", 0, NULL);
    SifLoadModule("rom0:PADMAN", 0, NULL);
    padInit(0);
    
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
 
	gsKit_clear(gsGlobal, GS_SETREG_RGBAQ(0,0xFF,0xFF,80,0));
	gsKit_queue_exec(gsGlobal);
	gsKit_sync_flip(gsGlobal);
	
	
	
	//loader
	memcpy((void*)LOADER_BASE, loader, size_loader);
	FlushCache(0);
	FlushCache(2);
    
static char relative_path[] = "main.elf";
	static char *argv[2];
    argv[0] = relative_path;   // e.g. "main.fbnx" or "games/game.elf"
    argv[1] = NULL;    
	
    static const char savepath[] = "host:";
    strcpy((char*)WORKPATH_ADDRESS, savepath);
    strcpy((char*)RELPATH_ADDRESS, "main.elf");

    *DEBUG_MARKER = 0x11;
    ExecPS2((void*)LOADER_BASE, NULL, 1, argv);   // argv can stay, we just won't trus
	
	while (1) {}
	
	return 0;
	
	
	
}

