#include "gfx.h"
#include <dmaKit.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include <kernel.h>
#include <gsToolkit.h>

GSGLOBAL *gsGlobal;
GSTEXTURE wallpaper;
GSTEXTURE fontfile;

//void gfx_init(void)
//{
//	dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
//				D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
//	dmaKit_chan_init(DMA_CHANNEL_GIF);
//
//	gsGlobal = gsKit_init_global();

//	gsGlobal->Mode = GS_MODE_PAL;
//	gsGlobal->Interlace = GS_INTERLACED;
//	gsGlobal->Field = GS_FIELD;
//	gsGlobal->Width = 640;
//	gsGlobal->Height = 480;
//	gsGlobal->DoubleBuffering = GS_SETTING_OFF;
//	gsGlobal->ZBuffering = GS_SETTING_OFF;
//	gsGlobal->PrimAlphaEnable = GS_SETTING_ON;

//	gsKit_init_screen(gsGlobal);
//	gsKit_mode_switch(gsGlobal, GS_ONESHOT);
//}


void gfx_init_cold(void)
{
    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
                D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

    gsGlobal = gsKit_init_global();
    gsGlobal->Mode = GS_MODE_PAL;
    gsGlobal->Interlace = GS_INTERLACED;
    gsGlobal->Field = GS_FIELD;
    gsGlobal->Width = 640;
    gsGlobal->Height = 480;
    gsGlobal->DoubleBuffering = GS_SETTING_OFF;
    gsGlobal->ZBuffering = GS_SETTING_OFF;
    gsGlobal->PrimAlphaEnable = GS_SETTING_ON;

    gsKit_init_screen(gsGlobal);      // ONLY call site, ever
    gsKit_mode_switch(gsGlobal, GS_ONESHOT);
}

void gfx_init_warm(void)
{
    HandoffInfo *h = handoff();

    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
                D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

    gsGlobal = gsKit_init_global();
    gsGlobal->Mode = h->Mode;
    gsGlobal->Interlace = h->Interlace;
    gsGlobal->Field = h->Field;
    gsGlobal->Width = h->Width;
    gsGlobal->Height = h->Height;
    gsGlobal->PSM = h->PSM;
    gsGlobal->FrameBuffer = h->FrameBuffer;
    gsGlobal->CurrentPointer = h->vram_watermark;
    gsGlobal->DoubleBuffering = GS_SETTING_OFF;
    gsGlobal->ZBuffering = GS_SETTING_OFF;
    gsGlobal->PrimAlphaEnable = GS_SETTING_ON;

    gsKit_mode_switch(gsGlobal, GS_ONESHOT);
    // deliberately NO gsKit_init_screen() here — that's what flashes the display
}



void gfx_clear(u64 color)
{
	gsKit_clear(gsGlobal, color);
}

void gfx_flip(void)
{
	gsKit_sync_flip(gsGlobal);
}
void gfx_exec(void)
{
	gsKit_queue_exec(gsGlobal);
}

int load_png(char *path, GSTEXTURE *texture)
{
	int ret = gsKit_texture_png(gsGlobal, texture, path);  // no & needed, texture is already a pointer
	if (ret != 0) {
		printf("Failed to load PNG: %s (err %d)\n", path, ret);
		return -1;
	}
	texture->Filter = GS_FILTER_NEAREST;
	return 0;
}

