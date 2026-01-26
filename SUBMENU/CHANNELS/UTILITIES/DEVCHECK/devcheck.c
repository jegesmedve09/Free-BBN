#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "../../../../gfx.h"
#include "../../../../utils.h"
#include "../../../../background.h"
#include "../../../../pad.h"
#include "../../../../menu.h"


typedef struct {
    const char *label;
    const char *path;
    int y;
    int x;
    
} DeviceLine;

DeviceLine devs[] = {
    { "MC0.....", "mc0:/",   120, 40},
    { "MC1.....", "mc1:/",   140, 40},
    { "MC2.....", "mc2:/",   160, 40},
    { "MC3.....", "mc3:/",   180, 40},
    { "MC4.....", "mc4:/",   200, 40},
    { "MC5.....", "mc5:/",   220, 40},
    { "MC6.....", "mc6:/",   240, 40},
    { "MC7.....", "mc7:/",   260, 40},
    { "MASS....", "mass:/",  280, 40},
    { "MASS0...", "mass0:/", 300, 40},
    { "MASS1...", "mass1:/", 320, 40},
    { "MASS2...", "mass2:/", 340, 40},
    { "MASS3...", "mass3:/", 360, 40},
    { "MASS4...", "mass4:/", 380, 40},
    { "MASS5...", "mass5:/", 400, 40},
    { "MASS6...", "mass6:/", 420, 40},
    { "MASS7...", "mass7:/", 440, 40},
    
    { "HOST....", "host:/",  120, 200},
    { "CDROM...", "cdrom:/", 140, 200},
    { "HDD.....", "hdd:/",   160, 200},
    { "SIO2....", "sio2:/",  180, 200},
    { "SMAP....", "SMAP:/",  200, 200},
};

int devcheck_show()
{
	gfx_fade_in(10);

	while(1)
	{
		background_update();
		gfx_draw_top_bar();
		
        gfx_draw_text("Device Checker", 40, 60,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),10, 4);
			
		char line[32];

		for (int i = 0; i < sizeof(devs)/16; i++)
		{
			snprintf(line, sizeof(line), "%s%d", devs[i].label, DEV_EXIST(devs[i].path));

			gfx_draw_text(line, devs[i].x, devs[i].y, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 5, 3);
        }
        
        gfx_draw_text("If there is no MULTITAP inserted", 220, 240,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
        gfx_draw_text("into the console, the MC items", 220, 260,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
        gfx_draw_text("will mirror onto the next", 220, 280,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
        gfx_draw_text("non-adjecent item, so if you see", 220, 300,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
        gfx_draw_text("OK,FAIL,OK,FAIL..with MC in the", 220, 320,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
        gfx_draw_text("first slot only, thats normal.", 220, 340,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
        gfx_draw_text("Vice versa if you have an MC", 220, 360,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
        gfx_draw_text("in the second slot only.", 220, 380,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
        
        gfx_draw_text("\xFF\x09 Back",5, 480,GS_SETREG_RGBAQ(0x70, 0x70, 0x70, 0x80, 0x00),5, 4);
		gfx_flip();
		gfx_exec();
		
		if (pad_get_buttons(0) & PAD_TRIANGLE)
		{
            gfx_fade_out(10);
            menu_reset_current_item();
            return 0;
		}
		
	}
}
