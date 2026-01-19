#include "gfx.h"
#include <tamtypes.h>
#include <gsKit.h>
#include "font.h"

GSGLOBAL *gsGlobal;

void gfx_init(void)
{
    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
                D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

    gsGlobal = gsKit_init_global();

    gsGlobal->Mode         = GS_MODE_PAL;
    gsGlobal->Interlace    = GS_INTERLACED;
    gsGlobal->Field        = GS_FIELD;
    gsGlobal->Width        = 640;
    gsGlobal->Height       = 512;
    gsGlobal->DoubleBuffering = GS_SETTING_OFF;
    gsGlobal->ZBuffering   = GS_SETTING_OFF;

    // === The important transparency settings ===
    gsGlobal->PrimAlphaEnable = GS_SETTING_ON;
    
    gsKit_init_screen(gsGlobal);

    // Normal "over" blending - most common and intuitive
    gsKit_set_primalpha(gsGlobal,
        GS_SETREG_ALPHA(0, 1, 0, 1, 0),   // A = As, B = 1-As
        0);

    gsKit_mode_switch(gsGlobal, GS_ONESHOT);
}

// Helper - easier to read & less error prone
u64 color = GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00);

// Important note about alpha values:
// 0x80 = 100% opaque
// 0x40 = 50%
// 0x20 = 25%
// 0x00 = invisible

void gfx_clear(u64 color)
{
    gsKit_clear(gsGlobal, color);
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

void gfx_reset(void)
{
    gsKit_queue_reset(gsGlobal->Os_Queue);
}

// Your font functions stay the same - they will now respect alpha automatically
void font_draw_char(char c, int x, int y, u64 color, int scale)
{
    unsigned char idx = (unsigned char)c;
    if (ascii_map[idx] == NULL) return;
    
    const Rect* rects = ascii_map[idx];
    for (int i = 0; rects[i].x != -1; i++)
    {
        int rx = x + (rects[i].x * scale + FONT_SCALE_BASE/2) / FONT_SCALE_BASE;
        int ry = y + (rects[i].y * scale + FONT_SCALE_BASE/2) / FONT_SCALE_BASE;
        int rw = (rects[i].w * scale + FONT_SCALE_BASE/2) / FONT_SCALE_BASE;
        int rh = (rects[i].h * scale + FONT_SCALE_BASE/2) / FONT_SCALE_BASE;
        
        if (rw < 1) rw = 1;
        if (rh < 1) rh = 1;
        
        gsKit_prim_sprite(gsGlobal, rx, ry, rx + rw, ry + rh, 1, color);
    }
}

void font_draw_icon(int c, int x, int y, u64 color, int scale)
{
    if (icon_map[c] == NULL) return;

    const Rect* rects = icon_map[c];

    for (int i = 0; rects[i].x != -1; i++)
    {
        int rx = x + (rects[i].x * scale + FONT_SCALE_BASE/2) / FONT_SCALE_BASE;
        int ry = y + (rects[i].y * scale + FONT_SCALE_BASE/2) / FONT_SCALE_BASE;
        int rw = (rects[i].w * scale + FONT_SCALE_BASE/2) / FONT_SCALE_BASE;
        int rh = (rects[i].h * scale + FONT_SCALE_BASE/2) / FONT_SCALE_BASE;

        if (rw < 1) rw = 1;
		if (rh < 1) rh = 1;

        gsKit_prim_sprite(gsGlobal, rx, ry, rx + rw, ry + rh, 1, color);
    }
	
}

void gfx_draw_text(const char* text, int x, int y, u64 color, int scale, int spacing)
{
    int pos_x = x;
	int advance;
    
    
    for (int i = 0; text[i]; i++)
    {
		
		if (text[i]=='\xFF')
		{
			advance = (ICON_BASE_WIDTH * scale + FONT_SCALE_BASE/2)/FONT_SCALE_BASE;
			
			if(advance < 1) advance=1;
			font_draw_icon(text[i+1], pos_x, y, color, scale);
			i++;
		}
		else
		{
				advance = (CHAR_BASE_WIDTH * scale + FONT_SCALE_BASE/2)/FONT_SCALE_BASE;
				if(advance < 1) advance=1;
				font_draw_char(text[i], pos_x, y, color, scale);
		}
		
        pos_x += advance + spacing;
        
    }
}

void gfx_draw_top_bar(void)
{
	gfx_draw_line(0, 26, 640, 26, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00));
	gfx_draw_text("FreeBBN", 5, 5, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 5, 4);
}	
