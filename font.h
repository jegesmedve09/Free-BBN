
#ifndef FONT_H
#define FONT_H

#include <tamtypes.h>

typedef struct {
    int x, y, w, h;
} Rect;

// Base char size
#define CHAR_BASE_WIDTH 16
#define CHAR_BASE_HEIGHT 32

extern Rect* font_map[128];

#endif
