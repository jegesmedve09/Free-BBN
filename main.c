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

#include "SUBMENU/ABOUT/about.h"
#include "SUBMENU/CHANNELS/channels.h"
#include "SUBMENU/SYSTEMSETTINGS/systemsettings.h"

const char* main_menu_items[] = {
    "Channels         -",
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
    
    //controller
    SifLoadModule("rom0:SIO2MAN", 0, NULL);
    SifLoadModule("rom0:PADMAN", 0, NULL);
    
	pad_init();
	
    sceCdInit(SCECdINIT);
    
	FuckAroundSilentlyMs(100);
    
    gfx_init();
    
    init_lava_background();
}

int main(void)
{
    init();
    gfx_flip();
    gfx_exec();
    
    
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
        
        menu_draw(main_menu_items, 6, 40, 100, 40, GS_SETREG_RGBAQ(255,255,0,128,0), GS_SETREG_RGBAQ(0x60, 0x60, 0x60, 0x80, 0), 4, 10, 8);
	
		gfx_draw_text("\xFF\x00/\xFF\x01 Navigate \xFF\x06 Select", 5, 480, GS_SETREG_RGBAQ(0x70, 0x70, 0x70, 0x80, 0x00), 5, 4);
        
        
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
			
			FuckAroundSilentlyMs(300);
			
			if (item == 0) { channels_show(); }
			if (item == 1) { systemsettings_show(); }
			if (item == 4) { about_show(); }
			if (item == 5) { PowerOff(); }
			
			FuckAroundSilentlyMs(300);
		}
        
		gfx_flip();
		gfx_exec();
		
    }
    
    
    
    
}
