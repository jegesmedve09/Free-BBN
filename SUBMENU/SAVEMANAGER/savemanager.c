#include <tamtypes.h>
#include <kernel.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <libpad.h>
#include "gfx.h"
#include "menu.h"
#include "background.h"
#include "pad.h"
#include "utils.h"      // assuming you have this

const char *menu_items[80];
static char *storage[80];
int savemanager_show(void) {
    DIR *d = opendir("mc0:/");
    if (!d) {
        printf("opendir mc0 failed\n");
        return -1;
    }

    struct dirent *ent;
	int amount_of_shit = 0;
    while ((ent = readdir(d)) != NULL) {
		strncpy(storage[amount_of_shit], ent->d_name, 255);
		storage[amount_of_shit][255] = '\0';
		menu_items[amount_of_shit] = storage[amount_of_shit];
		amount_of_shit++;
    }
    
    closedir(d);
    background_update();
    gfx_draw_top_bar();
    menu_draw(menu_items, amount_of_shit, 40, 120);
    gfx_flip();
    gfx_exec();

    FuckAroundSilentlyMs(1000);
    return 0;
}

