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
#include "utils.h"
#include "pad.h"
#include "background.h"
#include "menu.h"
#include "sound.h"
#include "irx.h"
#include "filemanager.h"
#include "settings.h"

#include "logscreen.h"

#include "SUBMENU/ABOUT/about.h"
#include "SUBMENU/CHANNELS/channels.h"
#include "SUBMENU/SYSTEMSETTINGS/systemsettings.h"

const char* main_menu_items[] = {
    "Channels         /",
    "System Settings  /",
    "Network Settings -",
    "Save Manager     -",
    "About            +",
    "Shutdown         +"
};

void init()
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
    sound_init();
    
    //controller
    SifLoadModule("rom0:SIO2MAN", 0, NULL);
    SifLoadModule("rom0:PADMAN", 0, NULL);
    pad_init();
    
	//memory card
    SifLoadModule("rom0:MCMAN", 0, NULL);
	SifLoadModule("rom0:MCSERV", 0, NULL);
	
	//USB mass
	SifExecModuleBuffer(irx_usbd, irx_usbd_size, 0, NULL, NULL);
	SifExecModuleBuffer(irx_usbhdfsd, irx_usbhdfsd_size, 0, NULL, NULL);
	
	FuckAroundSilentlyMs(2000);
	
	//graphics
    gfx_init();
	
	//settings
	settings_init();
	
	//reading background settings
	char **bg = settings_read_config("background");
	if (bg && bg[0] && bg[1] && bg[2] && bg[3] && bg[4]) {
		background_init(
			char_to_u8  (bg[0], 0),
			char_to_u8  (bg[1], 80),
			char_to_u8  (bg[2], 255),
			char_to_float(bg[3], 0.08f),
			char_to_float(bg[4], 1.2f)
		);
		free(bg[0]);  // frees the buffer
		free(bg);     // frees the array
	} else {
		background_init(0x00, 0x80, 0xFF, 0.12f, 1.2f);
	}
	
	//FuckAroundSilentlyMs(2000);
}

int main(void)
{
    init();
    //gfx_flip();
    //gfx_exec();
    
    for (int i = 0; i < 128; i+=2)
    {
        background_update();
		gfx_draw_text("FreeBBN", 184, 226, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, i, 0x00), 20, 4);
		gfx_flip();
		gfx_exec();
	}
	    
    for (int i = 128; i > 0; i-=3)
    {
        background_update();
		gfx_draw_text("FreeBBN", 184, 226, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, i, 0x00), 20, 4);
		gfx_flip();
		gfx_exec();
	}
    //sound_stop();
    while(1)
    {
        //gfx_flip();
        background_update();
        gfx_draw_top_bar();
        gfx_draw_text("Main Menu", 40, 60, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 10, 4);	
        
        menu_draw(main_menu_items, 6, 40, 120, 30, GS_SETREG_RGBAQ(255,255,0,128,0), GS_SETREG_RGBAQ(0x60, 0x60, 0x60, 0x80, 0), 4, 8, 6);
	
		gfx_draw_text("\xFF\x00/\xFF\x01 Navigate \xFF\x06 Select", 5, 480, GS_SETREG_RGBAQ(0x70, 0x70, 0x70, 0x80, 0x00), 5, 4);
		
		gfx_flip();
		gfx_exec();
		
        if(pad_get_buttons(0) & PAD_DOWN)
		{
			menu_increment();
			FuckAroundSilentlyMs(300);
		}
	
		if(pad_get_buttons(0) & PAD_UP)
		{
			menu_decrement();
			FuckAroundSilentlyMs(300);
		}
	
		if(pad_get_buttons(0) & PAD_CROSS)
		{			
			int item = menu_get_current_item();
			
			menu_reset_current_item();
			
			gfx_fade_out(10);
			
			if (item == 0) { channels_show(); }
			if (item == 1) { systemsettings_show(); }
			if (item == 3)
			{
				const char* file_extensions[] = {
					"None",
				};
				filemanager_show(file_extensions);
			}
			if (item == 4) { about_show(); }
			if (item == 5) { PowerOff(); }
			
			gfx_fade_in(10);
		}
		
    }
    
    
    
    
}
