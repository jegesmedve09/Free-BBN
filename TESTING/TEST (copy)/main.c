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

void init()
{	
	SifInitRpc(0);
    while (!SifIopReset("", 0)) {};
    while (!SifIopSync()) {};
    SifInitRpc(0);
    SifLoadFileInit();
    sbv_patch_enable_lmb();

    //sound
	SifExecModuleBuffer(irx_freesd, irx_freesd_size, 0, NULL, NULL);
	SifExecModuleBuffer(irx_audsrv, irx_audsrv_size, 0, NULL, NULL);
    //SifLoadModule("host:/freesd.irx", 0, NULL);
    //SifLoadModule("host:/audsrv.irx", 0, NULL);

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
	
	//FuckAroundSilentlyMs(2000);

	//graphics
    gfx_init();
	
    audio_init();
	
}

int main(void)
{
    init();
    load_png("host:/THEMES/Curse/main.png", &wallpaper);
    

    if (audio_stream_open(&snd_menu, "host:/THEMES/Curse/menu.wav", 1) != 0) {
        printf("Failed to open menu music\n");
    }
    if (audio_stream_open(&snd_select, "host:/THEMES/Curse/select.wav", 1) != 0) {
        printf("Failed to open menu music\n");
    }
    if (audio_stream_open(&snd_back, "host:/THEMES/Curse/back.wav", 1) != 0) {
        printf("Failed to open menu music\n");
    }

    while (1)
    {
        audio_stream_update(&snd_menu);
        
        gfx_draw_image(0, 0, &wallpaper,false,false);
        gfx_clear(GS_SETREG_RGBAQ(0x00,0x00,0x00,80,0x00));
        gfx_exec();
        gfx_flip();
        if (pad_get_pressed(0) && PAD_CROSS)
        {
			audio_stream_update(&snd_select);
		}
    }

    audio_stream_stop(&snd_menu);
    audio_stream_close(&snd_menu);
    audio_quit();
    return 0;
    
}
