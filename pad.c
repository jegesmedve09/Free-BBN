
#include "pad.h"
#include <libpad.h>

static char padBuf[2][256] __attribute__((aligned(64)));  // Buffer for both pads
static struct padButtonStatus buttons[MAX_PLAYERS];
static u32 old_pad[MAX_PLAYERS] = {0, 0};
static u32 new_pad[MAX_PLAYERS] = {0, 0};
static u32 paddata[MAX_PLAYERS];

void pad_init(void)
{
    padInit(0);

    // Open both ports
    if (padPortOpen(0, 0, padBuf[0]) == 0) return;
    if (padPortOpen(1, 0, padBuf[1]) == 0) return;  // Player 2 optional
}

static void update_pad(int player)
{
    if (player < 0 || player >= MAX_PLAYERS) return;

    int state = padGetState(player, 0);
    if (state != PAD_STATE_STABLE) {
        old_pad[player] = 0;
        new_pad[player] = 0;
        return;
    }

    padRead(player, 0, &buttons[player]);

    paddata[player] = 0xFFFF ^ buttons[player].btns;
    new_pad[player] = paddata[player] & ~old_pad[player];
    old_pad[player] = paddata[player];
}

s8 get_joy_x(int stick, int player)
{
    update_pad(player);
    if (player < 0 || player >= MAX_PLAYERS) return 0;

    if (stick == PAD_LEFT_STICK)  return (s8)(buttons[player].ljoy_h - 128);
    if (stick == PAD_RIGHT_STICK) return (s8)(buttons[player].rjoy_h - 128);
    return 0;
}

s8 get_joy_y(int stick, int player)
{
    update_pad(player);
    if (player < 0 || player >= MAX_PLAYERS) return 0;

    if (stick == PAD_LEFT_STICK)  return (s8)(buttons[player].ljoy_v - 128);
    if (stick == PAD_RIGHT_STICK) return (s8)(buttons[player].rjoy_v - 128);
    return 0;
}

u32 get_pad_buttons(int player)
{
    update_pad(player);
    return old_pad[player];
}

u32 get_pad_pressed(int player)
{
    update_pad(player);
    return new_pad[player];
}
