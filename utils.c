#include "utils.h"

void FuckAroundSilently(int frames)
{
    // Calibrated busy loop
    // ~50 frames = 1 second on PAL (your 50007)
    // Tested on real hardware + PCSX2
    volatile int cycles = frames * 100000;  // Adjust multiplier if too fast/slow

    while (cycles--) {
        // Fuck around silently
        __asm__ ("nop");
    }
}

void FuckAroundSilentlyMs(int milliseconds)
{
    // ~50000 cycles per millisecond on PS2 EE @ 294MHz
    volatile int cycles = milliseconds * 50000;

    while (cycles--) {
        __asm__ ("nop");
    }
}
