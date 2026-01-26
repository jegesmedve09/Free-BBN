#include <tamtypes.h>
#include <kernel.h>
#include <stdio.h>
#include <stdlib.h>

#include "gfx.h"
#include "background.h"
#include "utils.h"
#include "pad.h"
#include "menu.h"


char *filemanager_show(const char **file_extensions)
{
	gfx_fade_in(10);
	while (1)
	{
		background_update();
		gfx_draw_top_bar();
		gfx_flip();
		gfx_exec();
		if (pad_get_buttons(0) & PAD_TRIANGLE)
		{
			gfx_fade_out(10);
			menu_reset_current_item();
			return "";
		}
	}
}
