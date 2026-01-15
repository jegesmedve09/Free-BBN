
// shared_core.h
#ifndef SHARED_CORE_H
#define SHARED_CORE_H

#include <tamtypes.h>
#include <gsKit.h>  // For GSGLOBAL, etc.
#include "font.h"   // Your Rect, ascii_map, etc.
#include "gfx.h"
#include "pad.h"

typedef struct {
    // GFX
    GSGLOBAL *gsGlobal;
    //void (*gfx_init)(void);
    void (*gfx_clear)(u64 color);
    void (*gfx_draw_line)(int x1, int y1, int x2, int y2, u64 color);
    void (*gfx_draw_square)(int x, int y, int w, int h, u64 color);
    void (*gfx_draw_triangle)(int x1, int y1, int x2, int y2, int x3, int y3, u64 color);
    void (*gfx_flip)(void);
    void (*gfx_exec)(void);
    void (*gfx_reset)(void);
    void (*gfx_draw_text)(const char* text, int x, int y, u64 color, int scale, int spacing);  // Your rect-based text

    
    
    // SOUND
    //void (*sound_init)(void);
    //void (*sound_play)(int id, float volume);  // Example

    
    
    // INPUT
    //void (*pad_init)(void);
    s8 (*pad_get_joy_x)(int stick, int player);
    s8 (*pad_get_joy_y)(int stick, int player);
    u32 (*pad_get_buttons)(int player);
    u32 (*pad_get_pressed)(int player);
    
    
    

    // Font data (shared pointers/constants)
    Rect **ascii_map;
    Rect **icon_map;
    //int ICON_BASE_WIDTH;
    //int ICON_BASE_HEIGHT;
    //int CHAR_BASE_WIDTH;
    //int CHAR_BASE_HEIGHT;

    // Magic for validation
    u32 magic;
	#define CORE_MAGIC 0xDEADBEEF //wtf...
	
} SharedCore;

#define SHARED_CORE_ADDR 0x01FC0000  // Safe high addr (top of RAM, unlikely to be overwritten)

#endif
