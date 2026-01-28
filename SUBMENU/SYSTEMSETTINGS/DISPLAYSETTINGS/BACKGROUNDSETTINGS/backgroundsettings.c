#include <tamtypes.h>
#include <kernel.h>
#include <stdio.h>
#include <string.h>

#include "../../../../gfx.h"
#include "../../../../utils.h"
#include "../../../../background.h"
#include "../../../../pad.h"
#include "../../../../menu.h"
#include "../../../../settings.h"

static char R_str[72] = "Red: Error";
static char G_str[72]   = "Green: Error";
static char B_str[72]  = "Blue: Error";
static char min_str[72]  = "Minimum: Error";
static char mul_str[72]   = "Multiplier: Error";

static const char *backgroundsettings_info_items[5];

int backgroundsettings_show(void)
{
	gfx_fade_in(10);
	while (1)
	{
		
		snprintf(R_str, sizeof(R_str), "Red: %d", background_target_r);
		snprintf(G_str,   sizeof(G_str),   "Green: %d", background_target_g);
		snprintf(B_str,  sizeof(B_str),  "Blue: %d", background_target_b);
		snprintf(min_str,  sizeof(min_str),  "Minumum: %03f (go negatives for fun)", background_min_brightness);
		snprintf(mul_str,   sizeof(mul_str),   "Multiplier: %03f", background_brightness_multiplier);
		
		backgroundsettings_info_items[0] = R_str;
		backgroundsettings_info_items[1] = G_str;
		backgroundsettings_info_items[2] = B_str;
		backgroundsettings_info_items[3] = min_str;
		backgroundsettings_info_items[4] = mul_str;
		
		background_update();
		gfx_draw_top_bar();
        gfx_draw_text("Background Settings", 40, 60, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 10, 4);	
        menu_draw(backgroundsettings_info_items, 5, 40, 120);
        gfx_draw_text("\xFF\x00/\xFF\x01 Navigate  \xFF\x02/\xFF\x03 Change  \xFF\x09 Back", 5, 480, GS_SETREG_RGBAQ(0x70,0x70,0x70,0x80,0x00),5, 4);
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
			
			char data[32] = "";
			
			snprintf(data, sizeof(data), "%d\n%d\n%d\n%f\n%f\n", background_target_r, background_target_g, background_target_b, background_min_brightness, background_brightness_multiplier);
			
			settings_save_config("background", data);
			return 0;
		}
		
		if (pad_get_buttons(0) & PAD_LEFT)
		{
			int item = menu_get_current_item();
			if (item == 0) { if (background_target_r <= 0 ){ background_target_r = 0; }else{ background_target_r -= 1; }}
			if (item == 1) { if (background_target_g <= 0 ){ background_target_g = 0; }else{ background_target_g -= 1; }}
			if (item == 2) { if (background_target_b <= 0 ){ background_target_b = 0; }else{ background_target_b -= 1; }}
			if (item == 3) { if (background_min_brightness <= -0.5f ){ background_min_brightness = -0.5f; }else{ background_min_brightness -= 0.001f; }}
			if (item == 4) { if (background_brightness_multiplier <= -5.0f ){ background_brightness_multiplier = -5.0f; }else{ background_brightness_multiplier -= 0.01f; }}
			FuckAroundSilentlyMs(100);
		}
		
		if (pad_get_buttons(0) & PAD_RIGHT)
		{
			int item = menu_get_current_item();
			if (item == 0) { if (background_target_r >= 255 ){ background_target_r = 255; }else{ background_target_r += 1; }}
			if (item == 1) { if (background_target_g >= 255 ){ background_target_g = 255; }else{ background_target_g += 1; }}
			if (item == 2) { if (background_target_b >= 255 ){ background_target_b = 255; }else{ background_target_b += 1; }}
			if (item == 3) { if (background_min_brightness >= 0.5f ){ background_min_brightness = 0.5f; }else{ background_min_brightness += 0.001f; }}
			if (item == 4) { if (background_brightness_multiplier >= 5.0f ){ background_brightness_multiplier = 5.0f; }else{ background_brightness_multiplier += 0.01f; }}
			FuckAroundSilentlyMs(100);
		}
	}
}


