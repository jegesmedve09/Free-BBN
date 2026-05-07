#include <tamtypes.h>
#include <iopcontrol.h>
#include <kernel.h>          // for FlushCache
#include <sifrpc.h>          // for SifInitRpc, SifIopReset, etc.
#include <loadfile.h>        // load IRX

#include "gfx.h"
#include "pad.h"
#include "utils.h"
#include "elf_loader.h"

void init(void)
{
	SifInitRpc(0);
	while (!SifIopReset("", 0)) {};
	while (!SifIopSync()) {};
	SifInitRpc(0);
	
    SifLoadModule("rom0:SIO2MAN", 0, NULL);
    SifLoadModule("rom0:PADMAN", 0, NULL);

	pad_init();
	FuckAroundSilentlyMs(1000);
	gfx_init();

}

int main (void){
	
	init();
	
	gfx_flip();
	gfx_clear(GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00));
	gfx_draw_text("System Start...OK", 5, 5, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x00,0x00), 10, 4);
	gfx_exec();
	
	load_elf("host:MENU/SPLASH/splash.elf", 0, NULL);
}
