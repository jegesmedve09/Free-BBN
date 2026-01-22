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

int statmc0 = 1;
int statmc1 = 1;
int statmass = 1;
char buffermc0[1024];
char buffermc1[1024];
char buffermass[1024];

int fd;

int utilities_show()
{
	fd = open("mc0:/dummy.txt", O_RDONLY);
	if (fd < 0)
	{
		statmc0 = 0;

	}else
	{
		statmc0=1;
		int bytes_read = read(fd, buffermc0, sizeof(buffermc0));
		if (bytes_read > 0)
		{
			// Process buffer (null-terminate if string)
			buffermc0[bytes_read] = '\0';
		}
	}
	close(fd);
	
	fd = open("mc1:/dummy.txt", O_RDONLY);
	if (fd < 0)
	{
		statmc1 = 0;

	}else
	{
		statmc1=1;
		int bytes_read = read(fd, buffermc1, sizeof(buffermc1));
		if (bytes_read > 0)
		{
			// Process buffer (null-terminate if string)
			buffermc1[bytes_read] = '\0';
		}
	}
	close(fd);
	
	fd = open("mass:/dummy.txt", O_RDONLY);
	if (fd < 0)
	{
		statmass = 0;

	}else
	{
		statmass=1;
		int bytes_read = read(fd, buffermass, sizeof(buffermass));
		if (bytes_read > 0)
		{
			// Process buffer (null-terminate if string)
			buffermass[bytes_read] = '\0';
		}
	}
	close(fd);
	
	while(1)
	{
		update_lava_background();
		gfx_draw_top_bar();
		
        gfx_draw_text("Utilities", 40, 60,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),10, 4);
        
        if (statmc0 == 1)
        {	
			gfx_draw_text("MC0 OK", 40, 120,
				GS_SETREG_RGBAQ(0x80,0xFF,0x80,0x60,0x00), 5, 3);
			gfx_draw_text(buffermc0, 40, 160,
				GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x60,0x00), 5, 3);
        }
        else
        {
			gfx_draw_text("MC0 FAIL", 40, 120,
				GS_SETREG_RGBAQ(0xFF,0x80,0x80,0x60,0x00), 5, 3);			
		}
        
        if (statmc1 == 1)
        {	
			gfx_draw_text("MC1 OK", 40, 200,
				GS_SETREG_RGBAQ(0x80,0xFF,0x80,0x60,0x00), 5, 3);
			gfx_draw_text(buffermc1, 40, 240,
				GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x60,0x00), 5, 3);
        }
        else
        {
			gfx_draw_text("MC1 FAIL", 40, 200,
				GS_SETREG_RGBAQ(0xFF,0x80,0x80,0x60,0x00), 5, 3);			
		}
        
        if (statmass == 1)
        {	
			gfx_draw_text("MASS OK", 40, 280,
				GS_SETREG_RGBAQ(0x80,0xFF,0x80,0x60,0x00), 5, 3);
			gfx_draw_text(buffermass, 40, 320,
				GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x60,0x00), 5, 3);
        }
        else
        {
			gfx_draw_text("MASS FAIL", 40, 280,
				GS_SETREG_RGBAQ(0xFF,0x80,0x80,0x60,0x00), 5, 3);			
		}
        
        
        gfx_draw_text("\xFF\x00/\xFF\x01 Navigate \xFF\x06 Select \xFF\x09 Back",5, 480,GS_SETREG_RGBAQ(0x70, 0x70, 0x70, 0x80, 0x00),5, 4);
		gfx_flip();
		gfx_exec();
		
	}
}
