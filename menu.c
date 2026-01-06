#include "menu.h"

#include <elf-loader.h>

#include "gfx.h"
#include "sound.h"
#include "utils.h"
#include "settings.h"
#include "pad.h"

static u64 color;

static bool NEEDS_REDRAW = true;

const char* menu_items[] = {
    "Launch ELF      (in progress)",
    "Run CO or OUO   (in progress)",
    "About",
    "Restart console (in progress)",
    "Shutdown console",
    "",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "abcdefghijklmnopqrstuvwxyz",
    "-*/+<>?:|{}_)(&^%$#@!~.",
    "1234567890"
};

void menu_exec(int item){
	
	if (item == 0){}
	if (item == 2){
		gfx_clear(GS_SETREG_RGBAQ(0x60, 0x60, 0xFF, 0x00, 0x00)); // Dark purple
		gfx_exec();
		gfx_flip();
    
		font_draw_text("Free-BBN "VERSION_TEXT" "VERSION_ID, 5, 5, GS_SETREG_RGBAQ(0x00,0x00,0x00,0x00,0x00), 10, 2);
		font_draw_text("Created by: jegesmedue09", 5, 60, GS_SETREG_RGBAQ(0x00,0x00,0x00,0x00,0x00), 5, 4);
		font_draw_text("Uersion text: " VERSION_TEXT, 5, 60+30, GS_SETREG_RGBAQ(0x00,0x00,0x00,0x00,0x00), 5, 4);
		font_draw_text("Uersion number: "VERSION_ID, 5, 60+30+30, GS_SETREG_RGBAQ(0x00,0x00,0x00,0x00,0x00), 5, 4);
		font_draw_text("Project started on: Oecember 30. 2025.", 5, 60+30+30+30, GS_SETREG_RGBAQ(0x00,0x00,0x00,0x00,0x00), 5, 4);
		font_draw_text("ProjeKti aloitettu: JouluKuu 30. 2025.", 5, 60+30+30+30+30, GS_SETREG_RGBAQ(0x00,0x00,0x00,0x00,0x00), 5, 4);
		font_draw_text("https:||www.reddit.com|r|FreeBBN|", 5, 60+30+30+30+100, GS_SETREG_RGBAQ(0x00,0x00,0x00,0x00,0x00), 5, 4);
		font_draw_text("https:||github.com|jegesmedue09|Free-BBN", 5, 60+30+30+30+100+30, GS_SETREG_RGBAQ(0x00,0x00,0x00,0x00,0x00), 5, 4);
		font_draw_text("Press O to go bacK", 5, 60+30+30+30+100+30+100, GS_SETREG_RGBAQ(0x00,0x00,0x00,0x00,0x00), 5, 4);
		gfx_exec();
		gfx_flip();
		while (!(get_pad_buttons(0) & PAD_CIRCLE)) {
            FuckAroundSilentlyMs(1);
        }
		NEEDS_REDRAW=true;
		}
	if (item == 4){PowerOff();}
}

#define MENU_ITEM_COUNT 10
#define MENU_START_Y    40
#define MENU_LINE_HEIGHT 40  // Distance between lines
static int MENU_ITEM = 0;

void menu_show(void){while (1){
	
	if(NEEDS_REDRAW){
	color= GS_SETREG_RGBAQ(0x60, 0x60, 0xFF, 0x00, 0x00);
    gfx_clear(color);
	gfx_exec();
	gfx_flip();
    color = GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00);
    gfx_draw_line(0, 26, 640, 26, color);
	
	color = GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00);
        
	font_draw_text("FREE-BBN", 5, 5, color, 5, 4);
	font_draw_text("ALPHA", 100, 15, color, 2, 2);
	font_draw_text("Menu", 560, 5, color, 5, 4);
	
	
	for (int i = 0; i < MENU_ITEM_COUNT; i++) {
		int y = MENU_START_Y + i * MENU_LINE_HEIGHT;

		
		if (i == MENU_ITEM) {
			color = GS_SETREG_RGBAQ(0xFF, 0xFF, 0x00, 0x00, 0x00);  // Yellow selected
		} else {
			color = GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00);  // White normal
		}

		font_draw_text(menu_items[i], 20, y, color, 10, 4);
	}
		
	gfx_exec();
	gfx_flip();
	NEEDS_REDRAW=false;
	}
	
	if(get_pad_buttons(0) & PAD_DOWN){
		if(MENU_ITEM<MENU_ITEM_COUNT-1){
			MENU_ITEM++;
			}
			NEEDS_REDRAW=true;FuckAroundSilentlyMs(100);}
	if(get_pad_buttons(0) & PAD_UP){
		if(MENU_ITEM > 0){
			MENU_ITEM--;
			}
			NEEDS_REDRAW=true;FuckAroundSilentlyMs(100);}
	if(get_pad_buttons(0) & PAD_CROSS){menu_exec(MENU_ITEM);}

}}
