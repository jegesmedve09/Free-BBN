#include <tamtypes.h>
#include <kernel.h>
#include <stdio.h>
#include <string.h>

#include "../../../gfx.h"
#include "../../../utils.h"
#include "../../../background.h"
#include "../../../pad.h"
#include "../../../menu.h"

#include "BACKGROUNDSETTINGS/backgroundsettings.h"
#include "MENUSETTINGS/menusettings.h"


const char* displaysettings_items[] =
{
	"Background",
	"Menu"
};

int displaysettings_show(void)
{
	gfx_fade_in(10);
	while (1)
	{
		background_update();
		gfx_draw_top_bar();
        gfx_draw_text("Display Settings", 40, 60, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 10, 4);	
        menu_draw(displaysettings_items, 2, 40, 120);
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
		
		if (pad_get_buttons(0) & PAD_TRIANGLE)
		{
			gfx_fade_out(10);
			menu_reset_current_item();
			return 0;
		}
		
		if (pad_get_buttons(0) & PAD_CROSS)
		{
			gfx_fade_out(10);
			int item = menu_get_current_item();
			menu_reset_current_item();
			if (item == 0) { backgroundsettings_show(); }
			if (item == 1) { menusettings_show(); }
			gfx_fade_in(10);
			
		}
	}
}

