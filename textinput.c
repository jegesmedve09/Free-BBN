
#include <tamtypes.h>
#include <kernel.h>
#include <stdio.h>

#include "gfx.h"
#include "background.h"
#include "menu.h"
#include "pad.h"
#include "utils.h"


char *text = "";
char *full_text;
bool upper = false;

static void add_char_to_text(char character)
{
	text[strlen(text)] = character;
	text[strlen(text)+1] = '\0';
}


char *textinput_get_text(const char *msg)
{
	gfx_fade_in(20);
	while (1)
	{
		background_update();
		gfx_draw_top_bar();
        gfx_draw_text(msg, 40, 60, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 10, 4);
        gfx_draw_text(":", 30, 100, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 10, 4);        
        gfx_draw_text(text, 40, 100, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 10, 4);
        
		const char *uppercase[40]={
			"Q","W","E","R","T","Y","U","I","O","P",
			"A","S","D","F","G","H","J","K","L","\xFF\x03",
			"Z","X","C","V","B","N","M",".","-","\xFF\x00",
			"(",")","_"," "," "," "," "," "," ","(OK)",
		};
		const char *lowercase[40]={
			"q","w","e","r","t","y","u","i","o","p",
			"a","s","d","f","g","h","j","k","l","\xFF\x03",
			"z","x","c","v","b","n","m",".","-","\xFF\x01",
			"(",")","_"," "," "," "," "," "," ","(OK)",
		};
		if (upper)
		{
			menu_grid_draw(uppercase, 40, 10, 40, 300);
		}
		else
		{
			menu_grid_draw(lowercase, 40, 10, 40, 300);
		}
		gfx_flip();
		gfx_exec();
		
		if (pad_get_buttons(0) & PAD_CROSS)
		{
			int item = menu_get_current_item();
			if (upper)
			{
				if (item == 0) add_char_to_text('Q');
				if (item == 1) add_char_to_text('W');
				if (item == 2) add_char_to_text('E');
				if (item == 3) add_char_to_text('R');
				if (item == 4) add_char_to_text('T');
				if (item == 5) add_char_to_text('Y');
				if (item == 6) add_char_to_text('U');
				if (item == 7) add_char_to_text('I');
				if (item == 8) add_char_to_text('O');
				if (item == 9) add_char_to_text('P');
				
				if (item == 10) add_char_to_text('A');
				if (item == 11) add_char_to_text('S');
				if (item == 12) add_char_to_text('D');
				if (item == 13) add_char_to_text('F');
				if (item == 14) add_char_to_text('G');
				if (item == 15) add_char_to_text('H');
				if (item == 16) add_char_to_text('J');
				if (item == 17) add_char_to_text('K');
				if (item == 18) add_char_to_text('L');
				
				if (item == 20) add_char_to_text('Z');
				if (item == 21) add_char_to_text('X');
				if (item == 22) add_char_to_text('C');
				if (item == 23) add_char_to_text('V');
				if (item == 24) add_char_to_text('B');
				if (item == 25) add_char_to_text('N');
				if (item == 26) add_char_to_text('M');
			}
			else
			{
				if (item == 0) add_char_to_text('q');
				if (item == 1) add_char_to_text('w');
				if (item == 2) add_char_to_text('e');
				if (item == 3) add_char_to_text('r');
				if (item == 4) add_char_to_text('t');
				if (item == 5) add_char_to_text('y');
				if (item == 6) add_char_to_text('u');
				if (item == 7) add_char_to_text('i');
				if (item == 8) add_char_to_text('o');
				if (item == 9) add_char_to_text('p');
				
				if (item == 10) add_char_to_text('a');
				if (item == 11) add_char_to_text('s');
				if (item == 12) add_char_to_text('d');
				if (item == 13) add_char_to_text('f');
				if (item == 14) add_char_to_text('g');
				if (item == 15) add_char_to_text('h');
				if (item == 16) add_char_to_text('j');
				if (item == 17) add_char_to_text('k');
				if (item == 18) add_char_to_text('l');
				
				if (item == 20) add_char_to_text('z');
				if (item == 21) add_char_to_text('x');
				if (item == 22) add_char_to_text('c');
				if (item == 23) add_char_to_text('v');
				if (item == 24) add_char_to_text('b');
				if (item == 25) add_char_to_text('n');
				if (item == 26) add_char_to_text('m');
			}
			
			if (item == 27) add_char_to_text('.');
			if (item == 28) add_char_to_text('-');			
			if (item == 30) add_char_to_text('(');
			if (item == 31) add_char_to_text(')');
			if (item == 32) add_char_to_text('_');
			if (item == 33) add_char_to_text(' ');
			if (item == 34) add_char_to_text(' ');
			if (item == 35) add_char_to_text(' ');
			if (item == 36) add_char_to_text(' ');
			if (item == 37) add_char_to_text(' ');
			if (item == 38) add_char_to_text(' ');
			
			if (menu_get_current_item() == 19) { text[strlen(text)-1] = '\0'; }
			if (menu_get_current_item() == 29) { if (upper){ upper = false; } else { upper=true; } }
			if (menu_get_current_item() == 39) { gfx_fade_out(20); menu_reset_current_item(); return text; }
			FuckAroundSilentlyMs(300);
		}	
		
		if (pad_get_buttons(0) & PAD_LEFT)
		{
			menu_grid_left(); FuckAroundSilentlyMs(300);
		}
		
		if (pad_get_buttons(0) & PAD_RIGHT)
		{
			menu_grid_right(); FuckAroundSilentlyMs(300);
		}
		
		if (pad_get_buttons(0) & PAD_UP)
		{
			menu_grid_up(); FuckAroundSilentlyMs(300);
		}
		
		if (pad_get_buttons(0) & PAD_DOWN)
		{
			menu_grid_down(); FuckAroundSilentlyMs(300);
		}
	}
}
