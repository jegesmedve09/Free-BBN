#include "gfx.h"
#include "audio.h"
#include "pad.h"
#include "handoff.h"

int main(int argc, char *argv[])
{
    SifInitRpc(0);
    SifLoadFileInit();
    sbv_patch_enable_lmb();

    pad_init();          // rebinding RPC client, cheap, safe to redo
    audio_init();         // same — rebinds audsrv RPC, doesn't reload IOP module
    gfx_init_warm();       // uses handoff struct instead of resetting the screen

    load_png("host:/font.png", &fontfile);
    load_png("host:/THEMES/Curse/main.png", &wallpaper);
    audio_voice_open(0, "host:/THEMES/Curse/menu.wav", 1);
    audio_voice_play(0);

    while (1) {
        audio_mixer_update();
        gfx_draw_image(0, 0, &wallpaper, false, false);
        gfx_flip();
        gfx_exec();

        u32 pressed = pad_get_pressed(0);

        if (pressed & PAD_TRIANGLE) {
            // hand off to VIDEO_PLAYER.ELF
            HandoffInfo *h = handoff();
            strcpy(h->path, "host:/VIDEO_PLAYER.ELF");

            h->vram_watermark = gsGlobal->CurrentPointer; // save current watermark

            t_ExecData exec;
            SifLoadElf("host:/LOADER.ELF", &exec);
            SifExitRpc();
            char *a[1] = { h->path };
            ExecPS2((void*)exec.epc, (void*)exec.gp, 1, a);
        }
    }
    return 0;
}
