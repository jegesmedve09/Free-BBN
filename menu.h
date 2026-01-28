
#ifndef MENU_H
#define MENU_H

extern int menu_line_height;
extern u8 menu_selected_color_R;
extern u8 menu_selected_color_G;
extern u8 menu_selected_color_B;
extern u8 menu_default_color_R;
extern u8 menu_default_color_G;
extern u8 menu_default_color_B;
extern int menu_spacing;
extern int menu_selected_scale;
extern int menu_default_scale;
extern int menu_max_lines;

void menu_init(int MENU_LINE_HEIGHT, int SELECT_COLOR_R, int SELECT_COLOR_G, int SELECT_COLOR_B, int DEFAULT_COLOR_R, int DEFAULT_COLOR_G, int DEFAULT_COLOR_B, int SPACING, int SELECT_SCALE, int DEFAULT_SCALE, int MAX_LINES, int FADE_LINES);
void menu_draw(const char **menu_items, int MENU_ITEM_COUNT, int MENU_START_X, int MENU_START_Y);
void menu_increment(void);
void menu_decrement(void);
void menu_reset_current_item(void);
void menu_set_selected(int sel);
int menu_get_current_item(void);

#endif
