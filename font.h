
#ifndef FONT_H
#define FONT_H

#include <tamtypes.h>

typedef struct {
    int x, y, w, h;
} Rect;

// Base char size
#define CHAR_BASE_WIDTH 16
#define CHAR_BASE_HEIGHT 32

#define ICON_BASE_WIDTH 32
#define ICON_BASE_HEIGHT 32

#define IS_ICON(c)  ((unsigned char)(c) >= 0x01 && (unsigned char)(c) <= 0x20)

extern Rect* ascii_map[128];
extern Rect* icon_map[128];
#endif
