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
	gsGlobal->Height = 480;
	gsGlobal->DoubleBuffering = GS_SETTING_OFF;
	gsGlobal->ZBuffering = GS_SETTING_OFF;
	gsGlobal->PrimAlphaEnable = GS_SETTING_ON;

	gsKit_init_screen(gsGlobal);
	gsKit_mode_switch(gsGlobal, GS_ONESHOT);
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

void gfx_reset(void)
{
	gsKit_queue_reset(gsGlobal->Os_Queue);
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

void gfx_draw_image(int x, int y, GSTEXTURE *texture, bool xflip, bool yflip)
{
	int u1 = 0, u2 = texture->Width;
	int v1 = 0, v2 = texture->Height;

	if (xflip) {
		int tmp = u1;
		u1 = u2;
		u2 = tmp;
	}
	if (yflip) {
		int tmp = v1;
		v1 = v2;
		v2 = tmp;
	}

	gsKit_prim_sprite_texture(gsGlobal, texture,
		x, y,							  // x1, y1 on screen — always top-left
		u1, v1,							// u1, v1 — texture coord for top-left corner
		x + texture->Width, y + texture->Height, // x2, y2 on screen — always bottom-right
		u2, v2,							// u2, v2 — texture coord for bottom-right corner
		1,
		0x80808080);
}

//void gfx_draw_text(char *text, int x, int y)
//{
//	gsKit_prim_sprite_texture(gsGlobal, &fontfile,
//		x, y,							  // x1, y1 on screen — always top-left
//		0, 0,							// u1, v1 — texture coord for top-left corner
//		16,32, // x2, y2 on screen — always bottom-right
//		16, 32,							// u2, v2 — texture coord for bottom-right corner
//		1,
//		GS_SETREG_RGBAQ(255,255,255,128,0));//0x80808080);
//	
//}
void gfx_draw_text(char *text, int x, int y)
{
    // 1. Create a local, mutable copy of the string
    char *text_copy = strdup(text); 
    if (!text_copy) return;

    int cursor_x = x;
    char *token = strtok(text_copy, ",");

    while (token != NULL) {
        int index = atoi(token);
        
        if (index > 0) {
            int cell_idx = index - 1; 
            int col = cell_idx % 32;
            int row = cell_idx / 32;
            
            int u1 = col * 16;
            int v1 = row * 32;
            
            gsKit_prim_sprite_texture(gsGlobal, &fontfile,
                cursor_x, y, 
                u1, v1, 
                cursor_x + 16, y + 32, 
                u1 + 16, v1 + 32, 
                1, 
                GS_SETREG_RGBAQ(255, 255, 255, 128, 0));

            cursor_x += 16;
        }
        
        // Handle spacing (indices 27-32)
        if (index >= 27 && index <= 32) {
            cursor_x += 8;
        }

        token = strtok(NULL, ",");
    }
    
    // 2. Free the copy to prevent memory leaks!
    free(text_copy);
}
