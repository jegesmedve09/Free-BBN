
#ifndef MENU_H
#define MENU_H

void menu_draw(const char **menu_items, int MENU_ITEM_COUNT, int MENU_START_X, int MENU_START_Y, int MENU_LINE_HEIGHT, u64 SELECT_COLOR, u64 DEFAULT_COLOR, int SPACING, int SELECT_SCALE, int DEFAULT_SCALE);

void menu_increment(void);
void menu_decrement(void);

void menu_reset_current_item(void);

void menu_set_selected(int sel);

int menu_get_current_item(void);

#endif
