#include "splash.h"
#include "gfx.h"
#include "sound.h"
#include "utils.h"
#include "settings.h"

u64 color;

void splash_show(void)
{
	
    // Fade to bright cyan so you SEE something
    for (int a = 0; a < 255; a += 5) {
        color = GS_SETREG_RGBAQ(0x60, 0x60, a, 0x00, 0x00);
        gfx_clear(color);
        //FuckAroundSilentlyMs(100);
    }

    // Hold magenta 10 seconds
    //for (int i = 0; i < 640; i=i+1) {
    //    u64 color = GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00);
    //    gfx_draw_line(0,50,i,50,color);
    //    gfx_exec();
    //    gfx_flip();
    //}
    
    color = GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00);
    gfx_draw_line(0, 50, 640, 50, color);
    gfx_flip();
    
    //F
    gfx_draw_line(10, 10, 10, 40, color);
    gfx_draw_line(10, 10, 30, 10, color);
    gfx_draw_line(10, 20, 30, 20, color);
    //r
    gfx_draw_line(30, 25, 30, 40, color);
    gfx_draw_line(30, 25, 40, 25, color);
    //e
    gfx_draw_line(45, 25, 45, 40, color);
    gfx_draw_line(45, 25, 55, 25, color);
    gfx_draw_line(45, 30, 55, 30, color);
    gfx_draw_line(45, 40, 55, 40, color);
    gfx_draw_line(55, 25, 55, 30, color);
    //e
    gfx_draw_line(60, 25, 60, 40, color);
    gfx_draw_line(60, 25, 70, 25, color);
    gfx_draw_line(60, 30, 70, 30, color);
    gfx_draw_line(60, 40, 70, 40, color);
    gfx_draw_line(70, 25, 70, 30, color);
    //B
    gfx_draw_line(80, 10, 80, 40, color);
    gfx_draw_line(80, 10, 90, 20, color);
    gfx_draw_line(90, 20, 80, 30, color);
    gfx_draw_line(80, 30, 90, 40, color);
    gfx_draw_line(90, 40, 80, 40, color);
    //B
    gfx_draw_line(95, 10, 95, 40, color);
    gfx_draw_line(95, 10, 105, 20, color);
    gfx_draw_line(105, 20, 95, 30, color);
    gfx_draw_line(95, 30, 105, 40, color);
    gfx_draw_line(105, 40, 95, 40, color);
    //N
    gfx_draw_line(110, 10, 110, 40, color);
    gfx_draw_line(120, 10, 120, 40, color);
    gfx_draw_line(110, 10, 120 ,40, color);
	
	
	color = GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00);
	gfx_draw_square(0, 0, 640 ,512, color);
	
	color = GS_SETREG_RGBAQ(0x60, 0x20, 0x20, 0x00, 0x00);
	gfx_draw_square(5, 5, 16, 32, color);
	
	
	color = GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00);
	font_draw_text("A", 5, 5, color, 1);
	//gfx_draw_square(0, 0, 50, 10, color);

    gfx_exec();
    gfx_flip();
}
