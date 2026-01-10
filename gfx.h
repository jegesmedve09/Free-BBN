#ifndef GFX_H
#define GFX_H
#include <gsKit.h>

extern GSGLOBAL *gsGlobal;

void gfx_init(void);
void gfx_clear(u64 color);
void gfx_draw_raw(const char* file_path, int x, int y, int width, int height, float alpha);

void gfx_draw_line(int x1, int y1, int x2, int y2, u64 color);  // NEW
void gfx_draw_square(int x, int y, int w, int h, u64 color);  // NEW
void gfx_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, u64 color);  // NEW
void gfx_flip(void);
void gfx_exec(void);
void gfx_reset(void);


#define FONT_SCALE_BASE 10  // 10 = normal size (32x16)
void gfx_draw_text(const char* text, int x, int y, u64 color, int scale, int spacing);

#endif
