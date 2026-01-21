#include <tamtypes.h>
#include <kernel.h>

#include <sifrpc.h>
#include <loadfile.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


#include "../../../gfx.h"
#include "../../../utils.h"
#include "../../../background.h"
#include "../../../pad.h"
#include "../../../menu.h"

int stats = 1;
char buffer[1024];

int utilities_show()
{
	int fd = open("mc0:/dummy.txt", O_RDONLY);
	if (fd < 0)
	{
		stats = 0;

	}else
	{
		stats=1;
		int bytes_read = read(fd, buffer, sizeof(buffer));
		if (bytes_read > 0)
		{
			// Process buffer (null-terminate if string)
			buffer[bytes_read] = '\0';
		}
	}
	close(fd);
	
	while(1)
	{
		update_lava_background();
		gfx_draw_top_bar();
		
        gfx_draw_text("Utilities", 40, 60,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),10, 4);
        
        if (stats == 1)
        {	
			gfx_draw_text("MC0 OK", 40, 120,
				GS_SETREG_RGBAQ(0x80,0xFF,0x80,0x60,0x00), 5, 3);
			gfx_draw_text(buffer, 40, 160,
				GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x60,0x00), 5, 3);
        }
        else
        {
			gfx_draw_text("MC0 FAIL", 40, 120,
				GS_SETREG_RGBAQ(0xFF,0x80,0x80,0x60,0x00), 5, 3);			
		}
        
        
        gfx_draw_text("\xFF\x00/\xFF\x01 Navigate \xFF\x06 Select \xFF\x09 Back",5, 480,GS_SETREG_RGBAQ(0x70, 0x70, 0x70, 0x80, 0x00),5, 4);
		gfx_flip();
		gfx_exec();
		
	}
}
