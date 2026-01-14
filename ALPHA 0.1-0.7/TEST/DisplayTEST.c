#include <stdio.h>
#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <gsKit.h>
#include <dmaKit.h>

int main(void)
{
    SifInitRpc(0);

    // Init DMA
    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
                D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

    // Global GS context
    GSGLOBAL *gsGlobal = gsKit_init_global();

    // Video mode setup (NTSC; change to GS_MODE_PAL if your console/TV is PAL)
    gsGlobal->Mode = GS_MODE_NTSC;
    gsGlobal->Interlace = GS_INTERLACED;
    gsGlobal->Field = GS_FIELD;
    gsGlobal->Width = 640;
    gsGlobal->Height = 448;
    gsGlobal->PSM = GS_PSM_CT32;
    gsGlobal->PSMZ = GS_PSMZ_16S;
    gsGlobal->DoubleBuffering = GS_SETTING_ON;
    gsGlobal->ZBuffering = GS_SETTING_ON;  // Turn ON — fixes black screen in many cases/emulators

    gsKit_init_screen(gsGlobal);

    // Use ONESHOT mode (more compatible than PERSISTENT on PCSX2)
    gsKit_mode_switch(gsGlobal, GS_ONESHOT);

    u64 Red = GS_SETREG_RGBAQ(0xFF, 0x00, 0x00, 0x80, 0x00);

    // Main loop
    while (1)
    {
        gsKit_clear(gsGlobal, Red);

        gsKit_queue_exec(gsGlobal);     // Explicit queue exec (needed in some modes)
        gsKit_sync_flip(gsGlobal);      // Vsync + buffer flip
    }

    return 0;
}
