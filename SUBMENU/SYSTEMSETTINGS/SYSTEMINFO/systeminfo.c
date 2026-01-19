#include <tamtypes.h>
#include <kernel.h>
#include <stdio.h>
#include <fcntl.h>       // O_RDONLY
#include <unistd.h>      // read(), close()
#include <string.h>      // strncmp(), strncpy()
#include <stdlib.h>      // for possible atoi() etc later

#include "../../../gfx.h"
#include "../../../pad.h"
#include "../../../background.h"
#include "../../../menu.h"

#define SYSTEM_INFO_ITEM_COUNT   6
#define SYSTEM_INFO_START_Y      160
#define SYSTEM_INFO_START_X      40
#define SYSTEM_INFO_LINE_HEIGHT  38


static char model_str[72]   = "Model: Unknown";
static char region_str[72]  = "Region: Unknown";
static char romver_str[72]  = "ROMVER: Failed to read";
static char ps1drv_str[72]  = "PS1 Driver: Not detected";


static const char *system_info_items[SYSTEM_INFO_ITEM_COUNT];


static void load_system_info(void)
{
    char romver[16] = {0};
    int fd;

    fd = open("rom0:ROMVER", O_RDONLY);
    if (fd >= 0)
    {
        int len = read(fd, romver, sizeof(romver)-1);
        close(fd);

        if (len >= 14)
        {
            romver[len] = '\0';   // safety

            snprintf(romver_str, sizeof(romver_str), "ROMVER: %s", romver);

            char reg = romver[4];
            if      (reg == 'J') strncpy(region_str, "Region: Japan (NTSC-J)", sizeof(region_str));
            else if (reg == 'A') strncpy(region_str, "Region: America (NTSC-U/C)", sizeof(region_str));
            else if (reg == 'E') strncpy(region_str, "Region: Europe / PAL", sizeof(region_str));
            else if (reg == 'H') strncpy(region_str, "Region: Asia (Hong Kong)", sizeof(region_str));
            else if (reg == 'C') strncpy(region_str, "Region: China", sizeof(region_str));
            else if (reg == 'K') strncpy(region_str, "Region: Korea (NTSC-K)", sizeof(region_str));
            else                 snprintf(region_str, sizeof(region_str), "Region: Unknown / MechaPwn (%c)", reg);

            char ver[5] = {0};
            strncpy(ver, romver, 4);
            ver[4] = '\0';

			if (!strcmp(ver, "0100") || !strcmp(ver, "0101"))
				strcpy(model_str, "Model: SCPH-10000 / SCPH-15000 (Early JP)");
			else if (!strcmp(ver, "0110"))
				strcpy(model_str, "Model: SCPH-18000 (Debug / DevTool)");
			else if (!strcmp(ver, "0120"))
				strcpy(model_str, "Model: SCPH-3000x (Early JP)");
			else if (!strcmp(ver, "0150"))
				strcpy(model_str, "Model: SCPH-3000xR / 3500xR (JP)");
			else if (!strcmp(ver, "0160"))
				strcpy(model_str, "Model: SCPH-3500x / 3700x / 3900x (JP)");
			else if (!strcmp(ver, "0170"))
				strcpy(model_str, "Model: SCPH-500xx (Early US/EU/JP)");
			else if (!strcmp(ver, "0180"))
				strcpy(model_str, "Model: SCPH-500xx (Mid US/EU/JP)");
			else if (!strcmp(ver, "0190"))
				strcpy(model_str, "Model: SCPH-700xx (US/EU/JP)");
			else if (!strcmp(ver, "0200"))
				strcpy(model_str, "Model: SCPH-7500x / 7700x / 7900x (Slim)");
			else if (!strcmp(ver, "0210"))
				strcpy(model_str, "Model: SCPH-7500x / 7700x / 7900x (Slim, late)");
			else if (!strcmp(ver, "0220"))
				strcpy(model_str, "Model: SCPH-9000x (Slim, late) / SCPH-500xx late");
			else if (!strcmp(ver, "0230"))
				strcpy(model_str, "Model: SCPH-9000x late / PStwo (SCPH-9000x)");
			else
				snprintf(model_str, sizeof(model_str), "Model: Unknown / Custom / MechaPwn (%s)", ver);
        }
    }

	//ps1 (wont work on real hw)
    fd = open("rom0:PS1VER", O_RDONLY);
    if (fd >= 0)
    {
        char ps1ver[8] = {0};
        read(fd, ps1ver, sizeof(ps1ver)-1);
        close(fd);
        snprintf(ps1drv_str, sizeof(ps1drv_str), "PS1 Driver: %s", ps1ver);
    }

    
    system_info_items[0] = model_str;
    system_info_items[1] = region_str;
    system_info_items[2] = romver_str;
    system_info_items[3] = ps1drv_str;
}

int systeminfo_show(void)
{
    load_system_info();

    menu_set_selected(-1);

    while (1)
    {
        update_lava_background();
        gfx_draw_top_bar();

        gfx_draw_text("System Info", 40, 60,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),10, 4);
        menu_draw(system_info_items, SYSTEM_INFO_ITEM_COUNT, SYSTEM_INFO_START_X, SYSTEM_INFO_START_Y, SYSTEM_INFO_LINE_HEIGHT, GS_SETREG_RGBAQ(0x90,0x90,0x90,0x80,0), GS_SETREG_RGBAQ(0x90,0x90,0x90,0x80,0), 4, 8, 8);

        gfx_draw_text("\xFF\x09 Back", 5, 480, GS_SETREG_RGBAQ(0xA0,0xA0,0xA0,0x80,0), 5, 4);

        gfx_flip();
        gfx_exec();

        if (get_pad_buttons(0) & PAD_TRIANGLE)
        {
            menu_reset_current_item();
            return 0;
        }
    }
}
