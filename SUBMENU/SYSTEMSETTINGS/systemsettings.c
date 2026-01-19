#include <tamtypes.h>
#include <kernel.h>

#include "../../gfx.h"
#include "../../utils.h"
#include "../../background.h"
#include "../../pad.h"
#include "../../menu.h"

#include "SYSTEMINFO/systeminfo.h"
#include "DATEANDTIME/dateandtime.h"

#define SETTINGS_MENU_ITEM_COUNT 7
#define SETTINGS_MENU_START_Y    180
#define SETTINGS_MENU_START_X	40
#define SETTINGS_MENU_LINE_HEIGHT 40  // Distance between lines

const char* settings_menu_items[] = {
    "System Info    +",
    "Date and Time  -",
    "Display        -",
    "Sound          -",
    "Language       -",
    "Char input     -",
    "Keyboard       -"
};


int systemsettings_show(void)
{
	while (1)
	{
		update_lava_background();
        gfx_draw_top_bar();
        
        gfx_draw_text("System Settings", 40, 60,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),10, 4);
        menu_draw(settings_menu_items, SETTINGS_MENU_ITEM_COUNT,SETTINGS_MENU_START_X,SETTINGS_MENU_START_Y,SETTINGS_MENU_LINE_HEIGHT,GS_SETREG_RGBAQ(255,255,0,128,0),GS_SETREG_RGBAQ(0x60, 0x60, 0x60, 0x80, 0),4, 10, 8);
		gfx_draw_text("\xFF\x00/\xFF\x01 Navigate \xFF\x06 Select \xFF\x09 Back",5, 480,GS_SETREG_RGBAQ(0x70, 0x70, 0x70, 0x80, 0x00),5, 4);
        
        gfx_flip();
        gfx_exec();
        
        
        if(get_pad_buttons(0) & PAD_DOWN)
		{
			menu_increment();
			FuckAroundSilentlyMs(300);
		}
	
		if(get_pad_buttons(0) & PAD_UP)
		{
			menu_decrement();
			FuckAroundSilentlyMs(300);
		}
		
		if(get_pad_buttons(0) & PAD_TRIANGLE)
		{
			menu_reset_current_item();
			FuckAroundSilentlyMs(300);
			return 0;
		}
		
		if(get_pad_buttons(0) & PAD_CROSS)
		{
			int item = menu_get_current_item();
			menu_reset_current_item();
			FuckAroundSilentlyMs(300);
			if (item == 0){ systeminfo_show(); }
			if (item == 1){ dateandtime_show(); }
			FuckAroundSilentlyMs(300);
		}
	
	}
}
