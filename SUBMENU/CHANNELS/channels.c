#include <tamtypes.h>
#include <kernel.h>

#include "../../gfx.h"
#include "../../utils.h"
#include "../../background.h"
#include "../../pad.h"
#include "../../menu.h"

#include "GAMESCHANNEL/gameschannel.h"
#include "UTILITIES/utilities.h"
#include "PICTURES/pictures.h"

#define CHANNELS_MENU_ITEM_COUNT 6

const char* channels_menu_items[] = {
    "Games     /",
    "Music     -",
    "Video     -",
    "Pictures  /",
    "Network   -",
    "Utilities"
};


int channels_show(void)
{
	gfx_fade_in(10);
	while (1)
	{
		background_update();
        gfx_draw_top_bar();
        
        gfx_draw_text("Channels", 40, 60,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),10, 4);
        menu_draw(channels_menu_items, CHANNELS_MENU_ITEM_COUNT, 40, 120);
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
			if (item == 0){ gameschannel_show(); }
			if (item == 3){ pictures_show(); }
			if (item == 5){ utilities_show(); }
			gfx_fade_in(10);
			//FuckAroundSilentlyMs(300);
		}
	
	}
}
