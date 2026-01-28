#include <tamtypes.h>
#include <kernel.h>

#include "../../../gfx.h"
#include "../../../utils.h"
#include "../../../background.h"
#include "../../../pad.h"
#include "../../../menu.h"

#include "RUNDISC/rundisc.h"

#define GAMESCHANNEL_MENU_ITEM_COUNT 3

const char* gameschannel_menu_items[] = {
    "Collection     -",
    "Run Disc       + NWRH UNTS",
    "ELF Games      -"
};


int gameschannel_show(void)
{
	gfx_fade_in(10);
	while (1)
	{
		background_update();
        gfx_draw_top_bar();
        
        gfx_draw_text("Games Channel", 40, 60,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),10, 4);
        menu_draw(gameschannel_menu_items, GAMESCHANNEL_MENU_ITEM_COUNT, 40, 120);
		gfx_draw_text("\xFF\x00/\xFF\x01 Navigate \xFF\x06 Select \xFF\x09 Back",5, 480,GS_SETREG_RGBAQ(0x70, 0x70, 0x70, 0x80, 0x00),5, 4);
        
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
		
		if(pad_get_buttons(0) & PAD_TRIANGLE)
		{
			menu_reset_current_item();
			//FuckAroundSilentlyMs(300);
			gfx_fade_out(10);
			return 0;
		}
		
		if(pad_get_buttons(0) & PAD_CROSS)
		{
			int item = menu_get_current_item();
			menu_reset_current_item();
			//FuckAroundSilentlyMs(300);
			gfx_fade_out(10);
			if (item == 0){ }
			if (item == 1){ rundisc_show(); }
			gfx_fade_in(10);
			//FuckAroundSilentlyMs(300);
		}
	
	}
}

