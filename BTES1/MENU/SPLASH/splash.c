#include <tamtypes.h>
#include "../../gfx.h"

int main(int argc, char **argv)
{
    // Fake args to prevent any old code from calling rom0:OSDSYS
    if (argc == 0) argc = 1;

    // Re-init graphics (safe, fast, required in new ELF)
    gfx_init();

    // Main drawing loop — must have this!
    while (1)
    {
        // Clear screen to solid pink-purple (alpha must be 0x80!)
        gfx_clear(GS_SETREG_RGBAQ(0xFF, 0x60, 0xFF, 0x80, 0));

        // Draw big visible text
        gfx_draw_text("SPLASH SCREEN", 120, 180,
                      GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0), 8, 3);

        gfx_draw_text("Chained from INIT!", 140, 280,
                      GS_SETREG_RGBAQ(0x00, 0xFF, 0xFF, 0x80, 0), 5, 2);

        // If args passed, show it
        if (argc > 1) {
            gfx_draw_text("Args OK!", 200, 340,
                          GS_SETREG_RGBAQ(0xFF, 0xFF, 0x00, 0x80, 0), 4, 1);
        }

        // Flip and execute — this updates the screen
        gfx_flip();
        gfx_exec();
    }

    return 0; // Never reached
}
