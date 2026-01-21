#include <tamtypes.h>
#include <kernel.h>
#include <stdio.h>
#include <timer.h>

#include "../../../gfx.h"
#include "../../../pad.h"
#include "../../../background.h"
#include "../../../menu.h"

int ps;
int systeminfo_show(void)
{
    //load_system_info();  // ← keep your real loader if you want actual data later

    gfx_fade_in(10);

    while (1)
    {
        update_lava_background();
        gfx_draw_top_bar();
		gfx_draw_text("System Information", 40, 60,
				  GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00), 10, 4);

		gfx_draw_text("Yup. It's a PlayStation 2.", 40, 140,
				  GS_SETREG_RGBAQ(0xFF,0xFF,0x80,0x80,0x00), 8, 4);

		gfx_draw_text("No RGB lighting. No SSD. No 4K. Just vibes.", 40, 180,
				  GS_SETREG_RGBAQ(0xC0,0xC0,0xFF,0x80,0x00), 6, 3);

		gfx_draw_text("Laser still alive? Congrats, you're winning.", 40, 220,
				  GS_SETREG_RGBAQ(0xFF,0xA0,0xA0,0x80,0x00), 6, 3);

		gfx_draw_text("ROMVER: Probably something from 2000-something.", 40, 260,
				  GS_SETREG_RGBAQ(0x90,0xFF,0x90,0x80,0x00), 6, 3);

		gfx_draw_text("Enjoy it while the capacitors hold.", 40, 300,
				  GS_SETREG_RGBAQ(0xFF,0x80,0x80,0x80,0x00), 6, 3);
	
		gfx_draw_text("Still better than a Series S tho...", 40, 420,
		  GS_SETREG_RGBAQ(0x80,0xFF,0x80,0x60,0x00), 5, 3);

		gfx_draw_text("Press \xFF\x09 to escape this existential crisis", 5, 480,
				  GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00), 5, 4);	
		gfx_flip();
		gfx_exec();
		if (get_pad_pressed(0) & PAD_TRIANGLE)
		{
			gfx_fade_out(10);
			return 0;
		}	  
	}
		
}
