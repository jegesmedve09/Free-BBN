// filemgr.c
#include "filemgr.h"
#include "gfx.h"
#include "pad.h"

#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>



void OpenFileManager(void)
{
	while(!(get_pad_buttons(0) & PAD_START))
	{
		
		gfx_flip();
		gfx_clear(GS_SETREG_RGBAQ(0x60, 0x60, 0xFF, 0x00, 0x00));
		//gfx_draw_text()
		gfx_exec();
			
	}
};
