#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>      // For SifLoadModule
#include <gsKit.h>
#include <dmaKit.h>
#include <audsrv.h>
#include <libsd.h>
#include <iopcontrol.h>
#include <stdio.h>
#include <malloc.h>
#include "gfx.h"
#include "sound.h"
#include "splash.h"
#include "utils.h"

int main_old(void)
{
    SifInitRpc(0);
	
	while (!SifIopReset("", 0)) {}
    while (!SifIopSync()) {}

    SifInitRpc(0);
	
    // Load audsrv.irx from host: (PCSX2 sees your PC folder)
    // Change to "mc0:/BOOT/audsrv.irx" or "mass:/audsrv.irx" on real hardware
    SifLoadModule("rom0:LIBSD", 0, NULL);
    SifLoadModule("mass:/audsrv.irx", 0, NULL);

	FuckAroundSilentlyMs(1000);
    
    sound_init();
    
    gfx_init();
    
    FuckAroundSilentlyMs(1000);
    
    splash_show();

    // After splash → main menu (visible green test)
    while (1)
    {
        gfx_clear(GS_SETREG_RGBAQ(0x00, 0xFF, 0x00, 0x80, 0x00));  // Bright green
    }

    return 0;
}

int main(void)
{
    SifInitRpc(0);

    // Load libsd first (required for SPU2)
    SifLoadModule("rom0:LIBSD", 0, NULL);

    // Load audsrv.irx from USB
    int ret = SifLoadModule("mass:/audsrv.irx", 0, NULL);
    if (ret < 0) {
        printf("Failed to load audsrv.irx from USB\n");
    }

    // Delay for IOP to finish loading module
    FuckAroundSilentlyMs(1000);  // 1 second

    gfx_init();

    sound_init();

    PlaySound("mass:/sound/chime.raw");

    //splash_show();

    while (1)
    {
        gfx_clear(GS_SETREG_RGBAQ(0x00, 0xFF, 0x00, 0x80, 0x00));
    }

    return 0;
}
