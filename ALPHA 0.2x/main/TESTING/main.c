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
#include "video.h"



void init()
{
    SifInitRpc(0);
    while (!SifIopSync()) {};

    FuckAroundSilentlyMs(2000);

    //graphics
    gfx_init();
    *GS_BGCOLOR = 0xFFFFFF;
    pad_init();
    audio_init();
    video_init();
    
}
int main(void)
{
    *GS_BGCOLOR = 0x808080;
    FuckAroundSilentlyMs(1000);
    init();
    //load_png("THEMES/Curse/main.png", &wallpaper);

    audio_voice_open(0, "video.wav", 1);
    //audio_voice_open(1, "THEMES/Curse/select.wav", 0);
    //audio_voice_open(2, "THEMES/Curse/back.wav", 0);
    audio_voice_play(0);
    load_png("font.png", &fontfile);
    video_play(path_portableinator("video.m2v"),1);

    while (1)
    {
        audio_mixer_update();
        //gfx_draw_image(0, 0, &wallpaper,false,false);
        video_update();
        //audio_mixer_update();
        gfx_draw_text("20,8,5,27,17,21,9,3,11,27,2,18,15,23,14,27,6,15,24",0,0);
        gfx_flip();
        gfx_exec();
        gfx_reset();
        
        u32 pressed = pad_get_pressed(0);
        
        if (pressed & PAD_CROSS)
        {
            audio_voice_play(1);
        }
        
        if (pressed & PAD_CIRCLE)
        {
            audio_voice_play(2);
        }
    }

    audio_voice_stop(0);
    audio_voice_stop(1);
    audio_voice_stop(2);
    audio_quit();
    return 0;
    
}
