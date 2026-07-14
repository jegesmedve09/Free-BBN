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

void init()
{	
	//SifInitRpc(0);
	//while (!SifIopReset("", 0)) {};
	//while (!SifIopSync()) {};
	//SifInitRpc(0);
	//SifLoadFileInit();
	//sbv_patch_enable_lmb();

	//sound
	//SifExecModuleBuffer(irx_freesd, irx_freesd_size, 0, NULL, NULL);
	//SifExecModuleBuffer(irx_audsrv, irx_audsrv_size, 0, NULL, NULL);
	//SifLoadModule("host:/freesd.irx", 0, NULL);
	//SifLoadModule("host:/audsrv.irx", 0, NULL);

	//controller
	//SifLoadModule("rom0:SIO2MAN", 0, NULL);
	//SifLoadModule("rom0:PADMAN", 0, NULL);
	pad_init();
	
	//memory card
	//SifLoadModule("rom0:MCMAN", 0, NULL);
	//SifLoadModule("rom0:MCSERV", 0, NULL);
	
	//USB I/O
	//SifExecModuleBuffer(irx_iomanx, irx_iomanx_size, 0, NULL, NULL);
	//SifExecModuleBuffer(irx_filexio, irx_filexio_size, 0, NULL, NULL);
	
	//USB Mass
	//SifExecModuleBuffer(irx_usbd, irx_usbd_size, 0, NULL, NULL);
	//SifExecModuleBuffer(irx_usbhdfsd, irx_usbhdfsd_size, 0, NULL, NULL);
	
	
	//FuckAroundSilentlyMs(2000);

	//graphics
	gfx_init();
	
	audio_init();
	
}

int main(void)
{
	init();
	load_png("host:/font.png", &fontfile);
	load_png("host:/THEMES/Curse/main.png", &wallpaper);

	audio_voice_open(0, "host:/THEMES/Curse/menu.wav", 1);
	audio_voice_open(1, "host:/THEMES/Curse/select.wav", 0);
	audio_voice_open(2, "host:/THEMES/Curse/back.wav", 0);
	audio_voice_play(0);
	while (1)
	{
		audio_mixer_update();
		
		gfx_draw_image(0, 0, &wallpaper,false,false);
		//gfx_clear(GS_SETREG_RGBAQ(0x00,0x00,0x00,80,0x00));
		gfx_draw_text("20,8,5,27,17,21,9,3,11,27,2,18,15,23,14,27,6,15,24",0,0);
		gfx_flip();
		gfx_exec();
		
		u32 pressed = pad_get_pressed(0);
		
		if (pressed & PAD_CROSS)
		{
			audio_voice_play(1);
		}
		
		if (pressed & PAD_CIRCLE)
		{
			audio_voice_play(2);
		}
	}

	audio_voice_stop(0);
	audio_voice_stop(1);
	audio_voice_stop(2);
	audio_quit();
	return 0;
	
}
