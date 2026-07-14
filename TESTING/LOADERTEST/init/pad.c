
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

