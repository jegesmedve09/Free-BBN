
#include <tamtypes.h>
#include <kernel.h>

#include "../../../gfx.h"
#include "../../../utils.h"
#include "../../../background.h"
#include "../../../pad.h"

int dateandtime_show(void)
{
	while (1)
	{
		update_lava_background();
		gfx_draw_text("Im raging. No clock for you", 40, 40,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
		gfx_draw_text("Fucking PS2 pain in my asshole", 40, 70,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
		gfx_draw_text("Fancy JST time my ass", 40, 100,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
		gfx_draw_text("Do it yourself. The PS2 BIOS exists", 40, 130,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
		
		gfx_draw_text("To the PS2 Team:", 40, 190,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
		gfx_draw_text("Kiss my ass", 40, 220,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
		
		gfx_draw_text("To Sony:", 40, 280,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
		gfx_draw_text("Your RTC belongs in the shadow realm", 40, 310,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
		
		gfx_draw_text("May femboys attack SONY at night", 40, 370,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
		gfx_draw_text("  -jegesmedve09", 40, 400,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
		
		gfx_draw_text("Last Version that touched RTC: alpha+ v0.10", 40, 460,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),5, 4);
		
		gfx_draw_text("Press \xFF\x09 to go back", 5, 480, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00), 5, 4);
		gfx_flip();
		gfx_exec();
		
		if (get_pad_pressed(0) & PAD_TRIANGLE)
        {	return 0; }
	}
}
