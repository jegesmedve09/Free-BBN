#include <tamtypes.h>
#include "gfx.h"
#include "menu.h"

static int MENU_ITEM = 0;
int ITEM_COUNT = 0;

int menu_line_height;
u8 menu_selected_color_R;
u8 menu_selected_color_G;
u8 menu_selected_color_B;
u8 menu_default_color_R;
u8 menu_default_color_G;
u8 menu_default_color_B;
int menu_spacing;
int menu_selected_scale;
int menu_default_scale;

void menu_init(int MENU_LINE_HEIGHT, int SELECT_COLOR_R, int SELECT_COLOR_G, int SELECT_COLOR_B, int DEFAULT_COLOR_R, int DEFAULT_COLOR_G, int DEFAULT_COLOR_B, int SPACING, int SELECT_SCALE, int DEFAULT_SCALE)
{
	menu_line_height = MENU_LINE_HEIGHT;
	menu_selected_color_R = SELECT_COLOR_R;
	menu_selected_color_G = SELECT_COLOR_G;
	menu_selected_color_B = SELECT_COLOR_B;
	menu_default_color_R = DEFAULT_COLOR_R;
	menu_default_color_G = DEFAULT_COLOR_G;
	menu_default_color_B = DEFAULT_COLOR_B;
	menu_selected_scale = SELECT_SCALE;
	menu_default_scale = DEFAULT_SCALE;
	menu_spacing = SPACING;
}

void menu_draw(const char **menu_items, int MENU_ITEM_COUNT, int MENU_START_X, int MENU_START_Y)
{
	ITEM_COUNT= MENU_ITEM_COUNT;
	for (int i = 0; i < MENU_ITEM_COUNT; i++)
	{
		int y = MENU_START_Y + i * menu_line_height;
	
		if (i == MENU_ITEM)
		{
			gfx_draw_text(menu_items[i], MENU_START_X, y, GS_SETREG_RGBAQ(menu_selected_color_R, menu_selected_color_G, menu_selected_color_B, 0x80, 0), menu_selected_scale, menu_spacing);
		}
		else
		{
			gfx_draw_text(menu_items[i], MENU_START_X, y, GS_SETREG_RGBAQ(menu_default_color_R, menu_default_color_G, menu_default_color_B, 0x80, 0), menu_default_scale, menu_spacing);
		}
	}
}


void menu_increment()
{
	if(MENU_ITEM<ITEM_COUNT-1)
	{
		MENU_ITEM++;
	}
}

void menu_decrement()
{
	if(MENU_ITEM > 0)
	{
		MENU_ITEM--;
	}
}


int menu_get_current_item()
{
	return MENU_ITEM;
}

void menu_reset_current_item()
{
	MENU_ITEM = 0;
}

void menu_set_selected(int sel)
{
	MENU_ITEM = sel;
}
