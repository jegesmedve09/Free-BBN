#ifndef GFX_H
#define GFX_H
#include <gsKit.h>

extern GSGLOBAL *gsGlobal;
extern GSTEXTURE wallpaper;
extern GSTEXTURE fontfile;


void gfx_init(void);
void gfx_clear(u64 color);

void gfx_flip(void);
void gfx_exec(void);
void gfx_reset(void);

int load_png(char *path, GSTEXTURE *texture);
void gfx_draw_image(int x, int y, GSTEXTURE *texture, bool xflip, bool yflip);
void gfx_draw_text(char *text, int x, int y, u64 color);

#endif
