#include <tamtypes.h>
#include <kernel.h>

#include "../../info.h"
#include "../../gfx.h"
#include "../../background.h"
#include "../../pad.h"

int about_show(void)
{	
	for (int i = 0; i < 128; i+=2)
	{
		update_lava_background();
        gfx_draw_text("Free-BBN "VERSION_TEXT" "VERSION_ID, 5, 5, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 10, 2);
		gfx_draw_text("Created by: jegesmedve09", 5, 60, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
		gfx_draw_text("Version text: " VERSION_TEXT, 5, 60+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
		gfx_draw_text("Version number: "VERSION_ID, 5, 60+30+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
		gfx_draw_text("Project started on: December 30. 2025.", 5, 60+30+30+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
		gfx_draw_text("Projekti aloitettu: Joulukuu 30. 2025.", 5, 60+30+30+30+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
		gfx_draw_text("https://www.reddit.com/r/FreeBBN/", 5, 60+30+30+30+100, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
		gfx_draw_text("https://github.com/jegesmedve09/Free-BBN", 5, 60+30+30+30+100+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
		gfx_draw_text("Press \xFF\x09 to go back", 5, 60+30+30+30+100+30+100, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
		gfx_flip();
		gfx_exec();
	}
	
	
    while (1)
    {
        update_lava_background();		
        gfx_draw_text("Free-BBN "VERSION_TEXT" "VERSION_ID, 5, 5, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00), 10, 2);
		gfx_draw_text("Created by: jegesmedve09", 5, 60, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00), 5, 4);
		gfx_draw_text("Version text: " VERSION_TEXT, 5, 60+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00), 5, 4);
		gfx_draw_text("Version number: "VERSION_ID, 5, 60+30+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00), 5, 4);
		gfx_draw_text("Project started on: December 30. 2025.", 5, 60+30+30+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00), 5, 4);
		gfx_draw_text("Projekti aloitettu: Joulukuu 30. 2025.", 5, 60+30+30+30+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00), 5, 4);
		gfx_draw_text("https://www.reddit.com/r/FreeBBN/", 5, 60+30+30+30+100, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00), 5, 4);
		gfx_draw_text("https://github.com/jegesmedve09/Free-BBN", 5, 60+30+30+30+100+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00), 5, 4);
		gfx_draw_text("Press \xFF\x09 to go back", 5, 60+30+30+30+100+30+100, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00), 5, 4);
		gfx_flip();
		gfx_exec();

        if (get_pad_pressed(0) & PAD_TRIANGLE)
        {	
			for (int i = 128; i > 0; i-=2)
			{
				update_lava_background();
				gfx_draw_text("Free-BBN "VERSION_TEXT" "VERSION_ID, 5, 5, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 10, 2);
				gfx_draw_text("Created by: jegesmedve09", 5, 60, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
				gfx_draw_text("Version text: " VERSION_TEXT, 5, 60+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
				gfx_draw_text("Version number: "VERSION_ID, 5, 60+30+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
				gfx_draw_text("Project started on: December 30. 2025.", 5, 60+30+30+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
				gfx_draw_text("Projekti aloitettu: Joulukuu 30. 2025.", 5, 60+30+30+30+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
				gfx_draw_text("https://www.reddit.com/r/FreeBBN/", 5, 60+30+30+30+100, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
				gfx_draw_text("https://github.com/jegesmedve09/Free-BBN", 5, 60+30+30+30+100+30, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
				gfx_draw_text("Press \xFF\x09 to go back", 5, 60+30+30+30+100+30+100, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,i,0x00), 5, 4);
				gfx_flip();
				gfx_exec();
			}
			return 0;
		}
	}
}

