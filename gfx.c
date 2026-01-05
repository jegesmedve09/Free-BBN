#include "gfx.h"
#include <dmaKit.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "font.h"

GSGLOBAL *gsGlobal;

void gfx_init(void)
{
    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
                D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

    gsGlobal = gsKit_init_global();

    gsGlobal->Mode = GS_MODE_PAL;
    gsGlobal->Interlace = GS_INTERLACED;
    gsGlobal->Field = GS_FIELD;
    gsGlobal->Width = 640;
    gsGlobal->Height = 512;
    gsGlobal->DoubleBuffering = GS_SETTING_ON;
    gsGlobal->ZBuffering = GS_SETTING_OFF;
    gsGlobal->PrimAlphaEnable = GS_SETTING_ON;

    gsKit_init_screen(gsGlobal);
    gsKit_mode_switch(gsGlobal, GS_ONESHOT);
}

void gfx_clear(u64 color)
{
    gsKit_clear(gsGlobal, color);
    gsKit_queue_exec(gsGlobal);
    gsKit_sync_flip(gsGlobal);
}

void gfx_draw_line(int x1, int y1, int x2, int y2, u64 color)
{
    gsKit_prim_line(gsGlobal, x1, y1, x2, y2, 1, color);
}

void gfx_draw_square(int x, int y, int w, int h, u64 color)
{
    gsKit_prim_sprite(gsGlobal, x, y, x + w, y + h, 1, color);
}

void gfx_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, u64 color)
{
    gsKit_prim_triangle(gsGlobal, x1, y1, x2, y2, x3, y3, 1, color);
}



void gfx_flip(void)
{
    gsKit_sync_flip(gsGlobal);
}
void gfx_exec(void)
{
    gsKit_queue_exec(gsGlobal);
}

//void gfx_sync(void)
//{
//	gsKit_sync(gsGlobal);
//}

void gfx_reset(void)
{
	gsKit_queue_reset(gsGlobal->Os_Queue);
}


void font_draw_char(char c, int x, int y, u64 color, int scale)
{
    unsigned char idx = (unsigned char)c;
    if (idx >= 128 || font_map[idx] == NULL) return;

    Rect* rects = font_map[idx];

    for (int i = 0; rects[i].x != -1; i++) {
        int rx = x + (rects[i].x * scale + FONT_SCALE_BASE/2) / FONT_SCALE_BASE;
        int ry = y + (rects[i].y * scale + FONT_SCALE_BASE/2) / FONT_SCALE_BASE;
        int rw = (rects[i].w * scale + FONT_SCALE_BASE/2) / FONT_SCALE_BASE;
        int rh = (rects[i].h * scale + FONT_SCALE_BASE/2) / FONT_SCALE_BASE;

        if (rw < 1) rw = 1;
		if (rh < 1) rh = 1;

        gsKit_prim_sprite(gsGlobal, rx, ry, rx + rw, ry + rh, 1, color);
    }
}

void font_draw_text(const char* text, int x, int y, u64 color, int scale, int spacing)
{
    int pos_x = x;
    int advance = (CHAR_BASE_WIDTH * scale + FONT_SCALE_BASE/2)/FONT_SCALE_BASE;
	
	if(advance < 1) advance=1;
	
    for (int i = 0; text[i]; i++) {
        font_draw_char(text[i], pos_x, y, color, scale);
        pos_x += advance + spacing;
    }
}
