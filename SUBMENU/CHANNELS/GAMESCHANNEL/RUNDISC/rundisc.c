#include <tamtypes.h>
#include <kernel.h>
#include <stdio.h>
#include <timer.h>

#include "../../../../gfx.h"
#include "../../../../pad.h"
#include "../../../../background.h"
#include "../../../../menu.h"
#include "../../../../cdvd.h"

int rundisc_show(void)
{
    //load_system_info();  // ← keep your real loader if you want actual data later

    gfx_fade_in(10);

    while (1)
    {
        update_lava_background();
        gfx_draw_top_bar();
		gfx_draw_text("Run Disc", 40, 60,
				  GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00), 10, 4);
				  
		if (!disc_inserted())
		{
			gfx_draw_text("Please Insert Disc...", 40, 120, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 6, 4);
		}
		
		else if (!disc_ready())
		{
			gfx_draw_text("Waiting for Disc...", 40, 120, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 6, 4);
		}
		
		else if (disc_ready())
		{
			update_lava_background();
			gfx_draw_text("Executing...", 40, 120, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 6, 4);
			gfx_flip();
			gfx_exec();
			disc_launch_ps2_game();
		}
		
		gfx_flip();
		gfx_exec();
		
		if (get_pad_pressed(0) & PAD_TRIANGLE)
		{
			gfx_fade_out(10);
			return 0;
		}	
		  
	}
		
}

