#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <iopcontrol.h>
#include <loadfile.h>
#include <libcdvd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sbv_patches.h>

#include <sys/stat.h>

#include "gfx.h"
#include "audio.h"
#include "pad.h"
#include "utils.h"

void init()
{
    SifInitRpc(0);
    gfx_init();
    pad_init();
}

void draw_menu()
{
    gfx_clear(GS_SETREG_RGBAQ(0x00,0x00,170,80,0));
    gfx_draw_text("6,50,37,37,2,2,14,27,19,37,52,53,48,27,21,52,41,44,41,52,57",4,4, GS_SETREG_RGBAQ(255,255,255,128,0));
        
    gfx_draw_text("495",0,32,GS_SETREG_RGBAQ(255,255,255,128,0));
    gfx_draw_text("494",624,32,GS_SETREG_RGBAQ(255,255,255,128,0));

    for (int i = 16; i<620; i=i+16)
    {
        gfx_draw_text("487",i,32, GS_SETREG_RGBAQ(255,255,255,128,0));
    }
    for (int i = 64; i<416; i=i+32)
    {        
        gfx_draw_text("486",0,i,GS_SETREG_RGBAQ(255,255,255,128,0));
    }
    for (int i = 64; i<416; i=i+32)
    {        
        gfx_draw_text("486",624,i,GS_SETREG_RGBAQ(255,255,255,128,0));
    }
    for (int i = 16; i<620; i=i+16)
    {
        gfx_draw_text("487",i,416, GS_SETREG_RGBAQ(255,255,255,128,0));
    }
    gfx_draw_text("493",0,416,GS_SETREG_RGBAQ(255,255,255,128,0));
    gfx_draw_text("492",624,416,GS_SETREG_RGBAQ(255,255,255,128,0));
}

char *devices[8];
int device = 0;

// Dedicated function to handle scanning and rendering the progress bar once
void scan_devices()
{
    device = 0;

    draw_menu();
    gfx_draw_text("019,037,033,050,035,040,041,046,039,027,038,047,050,027,051,053,048,048,047,050,052,037,036,027,036,037,054,041,035,037,051,062,062,062", 16, 64, GS_SETREG_RGBAQ(255,255,255,128,0));
    for (int i = 16; i < 620; i = i + 16)
    {
        gfx_draw_text("449", i, 384, GS_SETREG_RGBAQ(255, 255, 255, 128, 0));
    }
    gfx_flip();
    gfx_exec();

    struct
    {
        const char* name;
        int x_pos;
    } checks[] =
    {
        {"mc0:/", 32},
        {"mc1:/", 48},
        {"mass0:/", 64},
        {"mass1:/", 80},
        {"mass2:/", 96},
        {"mass3:/", 112},
        {"pfs0:/", 128},
        {"pfs1:/", 144},
        {"pfs2:/", 160},
        {"pfs3:/", 176},
        {"host:/", 192}
    };

    for (int idx = 0; idx < 8; idx++)
    {
        if (DEV_EXIST(checks[idx].name) && device < 8) {
            devices[device] = (char*)checks[idx].name;
            device++;
        }

        draw_menu();
        gfx_draw_text("019,037,033,050,035,040,041,046,039,027,038,047,050,027,051,053,048,048,047,050,052,037,036,027,036,037,054,041,035,037,051,062,062,062", 16, 64, GS_SETREG_RGBAQ(255,255,255,128,0));
        
        for (int i = 16; i < 620; i = i + 16)
        {
            gfx_draw_text("449", i, 384, GS_SETREG_RGBAQ(255, 255, 255, 128, 0));
        }

        // Draw progress up to current block
        gfx_draw_text("417", 16, 384, GS_SETREG_RGBAQ(0, 255, 0, 128, 0));
        for (int p = 0; p <= idx; p++)
        {
            gfx_draw_text("449", checks[p].x_pos, 384, GS_SETREG_RGBAQ(0, 255, 0, 128, 0));
        }

        gfx_flip();
        gfx_exec();
    }
}

int main(void)
{
    init();
    load_png("font.png", &fontfile);
    
    audio_voice_play(0);
    u8 menuX = 0;
    
    while (1)
    {
        u32 press = pad_get_pressed(0);

        if (menuX == 0)
        {
            draw_menu();
            gfx_draw_text("23,37,44,35,47,45,37 ,27, 52,47 ,27, 52,40,37 ,27, 6,50,37,37,2,2,14 ,27, 41,46,51,52,33,44,44,37,50 ,93",16,64, GS_SETREG_RGBAQ(255,255,255,128,0));
            gfx_draw_text("020,040,041,051,027,041,046,051,052,033,044,044,037,050,027,055,041,044,044,027,041,046,051,052,033,044,044,027,006,050,037,037,002,002,014",16,128, GS_SETREG_RGBAQ(255,255,255,128,0));
            gfx_draw_text("047,046,052,047,027,057,047,053,050,027,051,057,051,052,037,045,062,062,062",16,160, GS_SETREG_RGBAQ(255,255,255,128,0));
            gfx_draw_text("004,047,027,057,047,053,027,055,041,051,040,027,052,047,027,048,050,047,035,037,037,036,091",16,224, GS_SETREG_RGBAQ(255,255,255,128,0));
            gfx_draw_text("413,414,025,037,051,063,048,050,047,035,037,037,036",4,444,GS_SETREG_RGBAQ(255,255,255,128,0));

            gfx_flip();
            gfx_exec();

            if (press & PAD_CROSS) 
            {
                menuX = 1; 
            }
        }
        else if (menuX == 1)
        {
            static int complete = 0;
            if (!complete)
            {
                scan_devices();
                complete = 1;
            }

            draw_menu();
            gfx_draw_text("019,037,033,050,035,040,041,046,039,027,038,047,050,027,051,053,048,048,047,050,052,037,036,027,036,037,054,041,035,037,051,062,062,062",16,64, GS_SETREG_RGBAQ(255,255,255,128,0));
            
            for (int i = 16; i<620; i=i+16)
            {
                gfx_draw_text("449",i,384, GS_SETREG_RGBAQ(255,255,255,128,0));
            }

            gfx_flip();
            gfx_exec();
        }
    }

    audio_voice_stop(0);
    audio_voice_stop(1);
    audio_voice_stop(2);
    audio_quit();
    return 0;
}
