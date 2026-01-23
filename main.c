#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <iopcontrol.h>
#include <loadfile.h>
#include <libcdvd.h>

#include "gfx.h"
#include "utils.h"
#include "pad.h"
#include "background.h"
#include "menu.h"
#include "sound.h"

#include "irx.h"

#include <stdio.h>


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
    
    gfx_init();
    
    gfx_clear(GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00));
    gfx_draw_text("BGFX: Lava...", 20, 20, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 5, 4);	
    gfx_flip();
    gfx_exec();
    init_lava_background();
    
    gfx_draw_text("IRX : LIBSD...", 20, 40, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 5, 4);	
    gfx_flip();
    gfx_exec();
    SifLoadModule("rom0:LIBSD", 0, NULL);
    
    gfx_draw_text("IRX : AUDSRV...", 20, 60, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 5, 4);	
    gfx_flip();
    gfx_exec();
    SifExecModuleBuffer(irx_audsrv_new, irx_audsrv_new_size, 0, NULL, NULL);
    
	//SifLoadModule("host:audsrv.irx", 0, NULL);

    gfx_draw_text("IRX : SIO2MAN...", 20, 80, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 5, 4);	
    gfx_flip();
    gfx_exec();
    SifLoadModule("rom0:SIO2MAN", 0, NULL);

    gfx_draw_text("IRX : PADMAN...", 20, 100, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 5, 4);	
    gfx_flip();
    gfx_exec();
    SifLoadModule("rom0:PADMAN", 0, NULL);
    

    gfx_draw_text("IRX : NCMAN...", 20, 120, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 5, 4);	
    gfx_flip();
    gfx_exec();
    SifLoadModule("rom0:MCMAN", 0, NULL);

    gfx_draw_text("IRX : MCSERV...", 20, 140, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 5, 4);	
    gfx_flip();
    gfx_exec();
	SifLoadModule("rom0:MCSERV", 0, NULL);
	
    gfx_draw_text("INIT: Pad...", 20, 160, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 5, 4);	
    gfx_flip();
    gfx_exec();
	pad_init();
	
	FuckAroundSilentlyMs(5000);
	gfx_fade_out(10);
}

int main(void)
{
    init();
    gfx_flip();
    gfx_exec();
    
    //sound_play_async("host:/startup.wav");
    
    for (int i = 0; i < 128; i+=2)
    {
        update_lava_background();
		gfx_draw_text("FreeBBN", 184, 226, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, i, 0x00), 20, 4);
		gfx_flip();
		gfx_exec();
	}
	    
    for (int i = 128; i > 0; i-=2)
    {
        update_lava_background();
		gfx_draw_text("FreeBBN", 184, 226, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, i, 0x00), 20, 4);
		gfx_flip();
		gfx_exec();
	}
    
    while(1)
    {
        //gfx_flip();
        update_lava_background();
        gfx_draw_top_bar();
        gfx_draw_text("Main Menu", 40, 60, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 10, 4);	
        
        menu_draw(main_menu_items, 6, 40, 120, 30, GS_SETREG_RGBAQ(255,255,0,128,0), GS_SETREG_RGBAQ(0x60, 0x60, 0x60, 0x80, 0), 4, 8, 6);
	
		gfx_draw_text("\xFF\x00/\xFF\x01 Navigate \xFF\x06 Select", 5, 480, GS_SETREG_RGBAQ(0x70, 0x70, 0x70, 0x80, 0x00), 5, 4);
        
		gfx_flip();
		gfx_exec();
        
        if(get_pad_buttons(0) & PAD_DOWN)
		{
			menu_increment();
			FuckAroundSilentlyMs(200);
		}
	
		if(get_pad_buttons(0) & PAD_UP)
		{
			menu_decrement();
			FuckAroundSilentlyMs(200);
		}
	
		if(get_pad_buttons(0) & PAD_CROSS)
		{			
			int item = menu_get_current_item();
			
			menu_reset_current_item();
			
			//FuckAroundSilentlyMs(300);
			
			gfx_fade_out(10);
			
			if (item == 0) { channels_show(); }
			if (item == 1) { systemsettings_show(); }
			if (item == 4) { about_show(); }
			if (item == 5) { PowerOff(); }
			
			gfx_fade_in(10);
			
			//FuckAroundSilentlyMs(300);
		}
		
    }
    
    
    
    
}
