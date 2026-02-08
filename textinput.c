
#include <tamtypes.h>
#include <kernel.h>

#include "gfx.h"
#include "background.h"

const char *text = "";

char *textinput_get_text(const char *msg)
{
	gfx_fade_in(20);
	while (1)
	{
		background_update();
		gfx_draw_top_bar();
        gfx_draw_text(msg, 40, 60, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 10, 4);
        gfx_flip();
        gfx_exec();
	}
}
