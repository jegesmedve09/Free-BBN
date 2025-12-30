#include "splash.h"
#include "gfx.h"
#include "sound.h"
#include "utils.h"

void splash_show(void)
{
    PlaySound("host:sound/startup.raw");

    // Fade to bright cyan so you SEE something
    for (int a = 0; a < 255; a += 1) {
        u64 color = GS_SETREG_RGBAQ(a, a, a, 0x00, 0x00);
        gfx_clear(color);
        //FuckAroundSilentlyMs(100);
    }

    // Hold magenta 10 seconds
    for (int i = 0; i < 500; i++) {
        gfx_clear(GS_SETREG_RGBAQ(0xFF, 0x00, 0xFF, 0x80, 0x00));
    }
}
