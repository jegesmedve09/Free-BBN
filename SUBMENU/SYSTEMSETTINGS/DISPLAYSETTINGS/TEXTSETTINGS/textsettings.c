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

static char line_height_str[72] = "Line Height: Error";

static char selected_color_R[72]="Select Red: Error";
static char selected_color_G[72]="Select Green: Error";
static char selected_color_B[72]="Select Blue: Error";
static char defaulted_color_R[72]="Default Red: Error";
static char defaulted_color_G[72]="Default Green: Error";
static char defaulted_color_B[72]="Default Blue: Error";

static char spacing_str[72]   = "Spacing: Error";
static char selected_scale_str[72]  = "Select Scale: Error";
static char default_scale_str[72]  = "Default Scale: Error";
static char max_lines_str[72]  = "Max Lines: Error";

static char fade_lines_str[72] = "Fade Lines: Error";

static const char *textsettings_info_items[12];

int textsettings_show(void)
{
	gfx_fade_in(10);
	while (1)
	{
		
		snprintf(line_height_str, sizeof(line_height_str), "Line Height: %d", menu_line_height);
		
		snprintf(selected_color_R, sizeof(selected_color_R), "Select Red: %d", menu_selected_color_R);
		snprintf(selected_color_G, sizeof(selected_color_G), "Select Green: %d", menu_selected_color_G);
		snprintf(selected_color_B, sizeof(selected_color_B), "Select Blue: %d", menu_selected_color_B);
		
		snprintf(defaulted_color_R, sizeof(defaulted_color_R), "Default Red: %d", menu_default_color_R);
		snprintf(defaulted_color_G, sizeof(defaulted_color_G), "Default Green: %d", menu_default_color_G);
		snprintf(defaulted_color_B, sizeof(defaulted_color_B), "Default Blue: %d", menu_default_color_B);
		
		snprintf(spacing_str, sizeof(spacing_str), "Spacing: %d", menu_spacing);
		snprintf(selected_scale_str, sizeof(selected_scale_str), "Select Scale: %d", menu_selected_scale);
		snprintf(default_scale_str, sizeof(default_scale_str), "Default Scale: %d", menu_default_scale);
		snprintf(max_lines_str, sizeof(max_lines_str), "Max Lines: %d", menu_max_lines);
		snprintf(fade_lines_str, sizeof(fade_lines_str), "Fade Lines: %d", menu_fade_lines);
		
		
		textsettings_info_items[0] = line_height_str;
		textsettings_info_items[1] = selected_color_R;
		textsettings_info_items[2] = selected_color_G;
		textsettings_info_items[3] = selected_color_B;
		textsettings_info_items[4] = defaulted_color_R;
		textsettings_info_items[5] = defaulted_color_G;
		textsettings_info_items[6] = defaulted_color_B;
		textsettings_info_items[7] = spacing_str;
		textsettings_info_items[8] = selected_scale_str;
		textsettings_info_items[9] = default_scale_str;
		textsettings_info_items[10] = max_lines_str;
		textsettings_info_items[11] = fade_lines_str;
		
		background_update();
		gfx_draw_top_bar();
        gfx_draw_text("Background Settings", 40, 60, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 10, 4);	
        menu_draw(textsettings_info_items, 12, 40, 120);
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
			
			char data[97] = "";
			
			snprintf(data, sizeof(data), "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", menu_line_height, menu_selected_color_R, menu_selected_color_G, menu_selected_color_B, menu_default_color_R, menu_default_color_G, menu_default_color_B, menu_spacing, menu_selected_scale, menu_default_scale, menu_max_lines, menu_fade_lines);
			
			settings_save_config("text", data);
			return 0;
		}
		
		if (pad_get_buttons(0) & PAD_LEFT)
		{
			int item = menu_get_current_item();
			if (item == 0) { if (menu_line_height <= 0 ){ menu_line_height = 0; }else{ menu_line_height -= 1; }}
			if (item == 1) { if (menu_selected_color_R <= 0 ){ menu_selected_color_R = 0; }else{ menu_selected_color_R -= 1; }}
			if (item == 2) { if (menu_selected_color_G <= 0 ){ menu_selected_color_G = 0; }else{ menu_selected_color_G -= 1; }}
			if (item == 3) { if (menu_selected_color_B <= 0 ){ menu_selected_color_B = 0; }else{ menu_selected_color_B -= 1; }}
			if (item == 4) { if (menu_default_color_R <= 0 ){ menu_default_color_R = 0; }else{ menu_default_color_R -= 1; }}
			if (item == 5) { if (menu_default_color_G <= 0 ){ menu_default_color_G = 0; }else{ menu_default_color_G -= 1; }}
			if (item == 6) { if (menu_default_color_B <= 0 ){ menu_default_color_B = 0; }else{ menu_default_color_B -= 1; }}
			if (item == 7) { if (menu_spacing <= 0 ){ menu_spacing = 0; }else{ menu_spacing -= 1; }}
			if (item == 8) { if (menu_selected_scale <= 0 ){ menu_selected_scale = 0; }else{ menu_selected_scale -= 1; }}
			if (item == 9) { if (menu_default_scale <= 0 ){ menu_default_scale = 0; }else{ menu_default_scale -= 1; }}
			if (item == 10) { if (menu_max_lines <= 1 ){ menu_max_lines = 1; }else{ menu_max_lines -= 1; }}
			if (item == 11) { if (menu_fade_lines <= 1 ){ menu_fade_lines = 1; }else{ menu_fade_lines -= 1; }}
			FuckAroundSilentlyMs(100);
		}
		
		if (pad_get_buttons(0) & PAD_RIGHT)
		{
			int item = menu_get_current_item();
			if (item == 0) { if (menu_line_height >= 100 ){ menu_line_height = 100; }else{ menu_line_height += 1; }}
			if (item == 1) { if (menu_selected_color_R >= 255 ){ menu_selected_color_R = 255; }else{ menu_selected_color_R += 1; }}
			if (item == 2) { if (menu_selected_color_G >= 255 ){ menu_selected_color_G = 255; }else{ menu_selected_color_G += 1; }}
			if (item == 3) { if (menu_selected_color_B >= 255 ){ menu_selected_color_B = 255; }else{ menu_selected_color_B += 1; }}
			if (item == 4) { if (menu_default_color_R >= 255 ){ menu_default_color_R = 255; }else{ menu_default_color_R += 1; }}
			if (item == 5) { if (menu_default_color_G >= 255 ){ menu_default_color_G = 255; }else{ menu_default_color_G += 1; }}
			if (item == 6) { if (menu_default_color_B >= 255 ){ menu_default_color_B = 255; }else{ menu_default_color_B += 1; }}
			if (item == 7) { if (menu_spacing >= 100 ){ menu_spacing = 100; }else{ menu_spacing += 1; }}
			if (item == 8) { if (menu_selected_scale >= 100 ){ menu_selected_scale = 100; }else{ menu_selected_scale += 1; }}
			if (item == 9) { if (menu_default_scale >= 100 ){ menu_default_scale = 100; }else{ menu_default_scale += 1; }}
			if (item == 10) { if (menu_max_lines >= 100 ){ menu_max_lines = 100; }else{ menu_max_lines += 1; }}
			if (item == 11) { if (menu_fade_lines >= 100 ){ menu_fade_lines = 100; }else{ menu_fade_lines += 1; }}
			FuckAroundSilentlyMs(100);
		}
	}
}


