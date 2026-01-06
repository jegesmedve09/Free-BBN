#include "splash.h"
#include "gfx.h"
#include "sound.h"
#include "utils.h"
#include "settings.h"

static u64 color;

void splash_show(void)
{
	
    // Fade to bright cyan so you SEE something
    for (int a = 0; a < 255; a += 5) {
        u8 r = (u8)(a * 0x60 / 255);
		u8 g = (u8)(a * 0x60 / 255);
		u8 b = (u8) a;

		color = GS_SETREG_RGBAQ(r, g, b, 0x00, 0x00);

		gfx_clear(color);
        //FuckAroundSilentlyMs(100);
    }
    
    color= GS_SETREG_RGBAQ(0x60, 0x60, 0xFF, 0x00, 0x00);
    gfx_clear(color);

    // Hold magenta 10 seconds
    for (int i = 0; i < 640; i+=5) {
        u64 color = GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00);
        gfx_draw_line(0,26,i,26,color);
        gfx_exec();
        gfx_flip();
    }
    
    color = GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00);
    gfx_draw_line(0, 26, 640, 26, color);
	
	color = GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00);
        
	font_draw_text("FREE-BBN", 5, 5, color, 5, 4);
	font_draw_text("ALPHA", 100, 15, color, 2, 2);
		
	gfx_exec();
	gfx_flip();
	
	FuckAroundSilentlyMs(2000);


}
