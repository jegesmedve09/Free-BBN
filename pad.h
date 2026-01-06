#ifndef PAD_H
#define PAD_H

#include <tamtypes.h>     // <-- THIS LINE WAS MISSING
#include <libpad.h>

// Stick numbers
#define PAD_LEFT_STICK  0
#define PAD_RIGHT_STICK 1

// Players
#define PAD_PLAYER_0    0
#define PAD_PLAYER_1    1

#define MAX_PLAYERS     2

#define PAD_LEFT      0x0080
#define PAD_DOWN      0x0040
#define PAD_RIGHT     0x0020
#define PAD_UP        0x0010
#define PAD_START     0x0008
#define PAD_R3        0x0004
#define PAD_L3        0x0002
#define PAD_SELECT    0x0001
#define PAD_SQUARE    0x8000
#define PAD_CROSS     0x4000
#define PAD_CIRCLE    0x2000
#define PAD_TRIANGLE  0x1000
#define PAD_R1        0x0800
#define PAD_L1        0x0400
#define PAD_R2        0x0200
#define PAD_L2        0x0100


void pad_init(void);

s8 get_joy_x(int stick, int player);
s8 get_joy_y(int stick, int player);

u32 get_pad_buttons(int player);
u32 get_pad_pressed(int player);

int pad_is_connected(int player);

#endif
