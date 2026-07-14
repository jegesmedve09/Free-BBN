#ifndef GFX_H
#define GFX_H
#include <gsKit.h>

extern GSGLOBAL *gsGlobal;
extern GSTEXTURE wallpaper;
extern GSTEXTURE fontfile;


void gfx_init_cold(void);
void gfx_init_warm(void);
void gfx_clear(u64 color);

void gfx_flip(void);
void gfx_exec(void);

int load_png(char *path, GSTEXTURE *texture);

#endif
