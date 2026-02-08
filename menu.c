#include <tamtypes.h>
#include "gfx.h"
#include "menu.h"

static int menu_item = 0;
int item_count = 0;

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

int menu_fade_lines;

int menu_max_lines;

static int scroll_offset = 0;

void menu_init(int MENU_LINE_HEIGHT, int SELECT_COLOR_R, int SELECT_COLOR_G, int SELECT_COLOR_B, int DEFAULT_COLOR_R, int DEFAULT_COLOR_G, int DEFAULT_COLOR_B, int SPACING, int SELECT_SCALE, int DEFAULT_SCALE, int MAX_LINES, int FADE_LINES)
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
	menu_max_lines = MAX_LINES;
	menu_fade_lines = FADE_LINES;
}

//this was 1/3 made by me, and 2/3 magical spaghetti thanx to Grok
void menu_draw(const char **MENU_ITEMS, int MENU_ITEM_COUNT, int MENU_START_X, int MENU_START_Y)
{
    item_count = MENU_ITEM_COUNT;
    if (item_count == 0) return;
    
    int visible_lines = menu_max_lines;
    if (visible_lines > item_count)
        visible_lines = item_count;

    int target_top = menu_item - (visible_lines / 2);

    if (target_top < 0)
    {
        target_top = 0;
	}
	
    int last_possible_top = item_count - visible_lines;
    if (last_possible_top < 0)
    {
		last_possible_top = 0;
	}
	
    if (target_top > last_possible_top)
    {
		target_top = last_possible_top;
	}
	
    scroll_offset = target_top;

    bool has_content_above = (scroll_offset > 0);
    bool has_content_below = (scroll_offset + visible_lines < item_count);

    for (int i = 0; i < visible_lines; i++)
    {
        int item_idx = scroll_offset + i;
        int screen_y   = MENU_START_Y + i * menu_line_height;

        u8 alpha = 0x80;

        if (has_content_above && i < menu_fade_lines)
        {
            float t = (float)(i + 1) / menu_fade_lines;
            alpha = (u8)(0x10 + (0x80 - 0x10) * t);
        }
        if (has_content_below && (visible_lines - 1 - i) < menu_fade_lines)
        {
            float t = (float)((visible_lines - 1 - i) + 1) / menu_fade_lines;
            alpha = (u8)(0x10 + (0x80 - 0x10) * t);
        }

        if (item_idx == menu_item)
        {
			alpha = 0x80;
		}
		
        u64 color = (item_idx == menu_item)
            ? GS_SETREG_RGBAQ(menu_selected_color_R,   menu_selected_color_G,   menu_selected_color_B,   alpha, 0)
            : GS_SETREG_RGBAQ(menu_default_color_R, menu_default_color_G, menu_default_color_B, alpha, 0);

        gfx_draw_text(MENU_ITEMS[item_idx], MENU_START_X, screen_y, color,
                      (item_idx == menu_item) ? menu_selected_scale : menu_default_scale,
                      menu_spacing);
    }
}


void menu_increment()
{
	if(menu_item<item_count-1)
	{
		menu_item++;
	}
}

void menu_decrement()
{
	if(menu_item > 0)
	{
		menu_item--;
	}
}


int menu_get_current_item()
{
	return menu_item;
}

int menu_get_offset()
{
	return scroll_offset;
}

void menu_reset_current_item()
{
	scroll_offset = 0;
	menu_item = 0;
}

void menu_set_selected(int sel)
{
	menu_item = sel;
}





// ==================== GRID MENU ====================

static int menu_columns = 1;   // will be set when drawing

void menu_grid_draw(const char** items, int num_items, int columns, int start_x, int start_y)
{
    if (columns < 1) columns = 1;
    menu_columns = columns;

    // You can adjust these values:
    int column_width = 50;        // <--- horizontal spacing between columns
    int line_height = 40;          // <--- vertical spacing (tune this)

    for (int i = 0; i < num_items; i++)
    {
        int row = i / columns;
        int col = i % columns;

        int x = start_x + col * column_width;
        int y = start_y + row * line_height;

        u64 color = (i == menu_item) ? 
                    GS_SETREG_RGBAQ(255, 255, 100, 128, 0) :   // selected color
                    GS_SETREG_RGBAQ(180, 180, 180, 128, 0);    // normal color

        gfx_draw_text(items[i], x, y, color, 10, 4);   // adjust size & style as you like
    }
}

// Simple & reliable movement (row-major)
void menu_grid_move(int delta)
{
    menu_item += delta;
    if (menu_item >= item_count) menu_item = 0;
    if (menu_item < 0) menu_item = item_count - 1;
}

void menu_grid_right() { menu_item++; }
void menu_grid_left()  { menu_item--; }
void menu_grid_down()  { menu_item += menu_columns; }
void menu_grid_up()    { menu_item -= menu_columns; }
