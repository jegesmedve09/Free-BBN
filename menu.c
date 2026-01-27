#include <tamtypes.h>
#include "gfx.h"
#include "menu.h"

static int MENU_ITEM = 0;
int ITEM_COUNT = 0;

int line_height;
u64 selected_color;
u64 default_color;
int spacing;
int selected_scale;
int default_scale;

void menu_init(int MENU_LINE_HEIGHT, u64 SELECT_COLOR, u64 DEFAULT_COLOR, int SPACING, int SELECT_SCALE, int DEFAULT_SCALE)
{
	line_height = MENU_LINE_HEIGHT;
	selected_color = SELECT_COLOR;
	default_color = DEFAULT_COLOR;
	selected_scale = SELECT_SCALE;
	default_color = DEFAULT_SCALE
	spacing = SPACING;
}

void menu_draw(const char **menu_items, int MENU_ITEM_COUNT, int MENU_START_X, int MENU_START_Y)
{
	ITEM_COUNT= MENU_ITEM_COUNT;
	for (int i = 0; i < MENU_ITEM_COUNT; i++)
	{
		int y = MENU_START_Y + i * line_height;
	
		if (i == MENU_ITEM)
		{
			gfx_draw_text(menu_items[i], MENU_START_X, y, selected_color, selected_scale, spacing);
		}
		else
		{
			gfx_draw_text(menu_items[i], MENU_START_X, y, default_color, default_scale, spacing);
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
