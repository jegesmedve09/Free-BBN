#include <tamtypes.h>
#include <kernel.h>
#include <timer.h>
#include "../../../../gfx.h"
#include "../../../../pad.h"
#include "../../../../background.h"
#include "../../../../menu.h"
#include "../../../../cdvd.h"


int rundisc_show(void)
{
    gfx_fade_in(10);
    while (1)
    {
        background_update();
        gfx_draw_top_bar();

        gfx_draw_text("Run Disc", 40, 60, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0), 10, 4);
        gfx_draw_text("\xFF\x09 Back \xFF\x06 Open/Close Tray", 5, 480, GS_SETREG_RGBAQ(0x70,0x70,0x70,0x80,0), 5, 4);

        if (!cdvd_disc_inserted()) {
            gfx_draw_text("Insert Disc...", 40, 140, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0), 6, 4);
        }
        else if (!cdvd_disc_ready()) {
            gfx_draw_text("Waiting...", 40, 140, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0), 6, 4);
        }
        else {
            gfx_fade_out(10);
            cdvd_launch_ps2_game();
            
            gfx_init();
            background_update();
            gfx_fade_in(10);
			
			while (1){
				background_update();
				gfx_draw_top_bar();
				gfx_draw_text("Run Disc", 40, 60, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0), 10, 4);
				gfx_draw_text("Failed to run disc. Is it a PS2 game?", 40, 140, GS_SETREG_RGBAQ(0xFF,0x80,0x80,0x80,0), 6, 4);
				gfx_draw_text("\xFF\x09 Back \xFF\x06 Open Tray", 5, 480, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0), 5, 4);

				gfx_flip();
				gfx_exec();
				
				if (pad_get_buttons(0) & PAD_TRIANGLE) {
					return 0;
				}
				if (pad_get_buttons(0) & PAD_CROSS) {
					cdvd_tray_open();
					break;
				}
			}
        }

        gfx_flip();
        gfx_exec();

        if (pad_get_buttons(0) & PAD_TRIANGLE) {
            gfx_fade_out(10);
            return 0;
		}

        if (pad_get_buttons(0) & PAD_CROSS) {
            cdvd_tray_toggle();
            return 0;
        }
    }
}
