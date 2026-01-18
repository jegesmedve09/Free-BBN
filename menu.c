#include <tamtypes.h>
#include "gfx.h"
#include "menu.h"

static int MENU_ITEM = 0;
int ITEM_COUNT = 0;
void menu_draw(const char **menu_items, int MENU_ITEM_COUNT, int MENU_START_X, int MENU_START_Y, int MENU_LINE_HEIGHT, u64 SELECT_COLOR, u64 DEFAULT_COLOR, int SPACING, int SELECT_SCALE, int DEFAULT_SCALE)
{
	ITEM_COUNT= MENU_ITEM_COUNT;
	for (int i = 0; i < MENU_ITEM_COUNT; i++)
	{
		int y = MENU_START_Y + i * MENU_LINE_HEIGHT;
	
		if (i == MENU_ITEM)
		{
			gfx_draw_text(menu_items[i], MENU_START_X, y, SELECT_COLOR, SELECT_SCALE, SPACING);
		}
		else
		{
			gfx_draw_text(menu_items[i], MENU_START_X, y, DEFAULT_COLOR, DEFAULT_SCALE, SPACING);
		//gfx_draw_text(menu_items[i], 20, y, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x00, 0x00), 5, 4);
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
