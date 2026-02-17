
#include <tamtypes.h>
#include <kernel.h>

#include <stdlib.h>

#include "../../../gfx.h"
#include "../../../utils.h"
#include "../../../background.h"
#include "../../../pad.h"
#include "../../../menu.h"
#include "../../../filemanager.h"
#include "../../../settings.h"

#include "image_handler.h"

const char* pictures_menu_items[] = {
    "Open file",
    "Slideshow (manual) -",
    "Slideshow (automatic) -",
    "Open Camera -",
};


void show_image(int *w, int *h, char *data)
{
	int pos = 0;
	gfx_fade_in(20);
	//while (1)
	//{
		for (int i=0; i < *h; i++)
		{
			for (int j=0; j < *w; j++)
			{
				gfx_draw_square(j, i, 1, 1, GS_SETREG_RGBAQ(data[pos],data[+1],data[pos+2], 0x80, 0x00));

				pos+=3;
				
			}
		}
		gfx_flip();
		gfx_exec();
	while(1){}
	
	
	
}

int pictures_show(void)
{
	gfx_fade_in(10);
	
	while (1)
	{
		background_update();
        gfx_draw_top_bar();
        
        gfx_draw_text("Pictures", 40, 60,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),10, 4);
        menu_draw(pictures_menu_items, 4, 40, 120);
		gfx_draw_text("\xFF\x00/\xFF\x01 Navigate \xFF\x06 Select \xFF\x09 Back",5, 480,GS_SETREG_RGBAQ(0x70, 0x70, 0x70, 0x80, 0x00),5, 4);
        
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
		
		if(pad_get_buttons(0) & PAD_TRIANGLE)
		{
			menu_reset_current_item();
			//FuckAroundSilentlyMs(300);
			gfx_fade_out(10);
			return 0;
		}
		
		if(pad_get_buttons(0) & PAD_CROSS)
		{
			char *file_path;
			int item = menu_get_current_item();
			menu_reset_current_item();
			gfx_fade_out(10);
			if (item == 0)
			{
				const char *args[1] = {"ppm", NULL};
				file_path = filemanager_show(args);
				
				char *buffer = NULL;
				int width[64];
				int height[64];
				char data[1024*1024];
				image_load(file_path, &buffer, data, *width, *height);
				show_image(width, height, data);
				free(buffer);
			}
		}
	
	}
}
