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

void init(void){
	
	SifInitRpc(0);
    while (!SifIopReset("", 0)) {};
    while (!SifIopSync()) {};
    SifInitRpc(0);
	
    gfx_init();
    gfx_flip();
    gfx_clear(GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00));
    gfx_exec();
}

int main(void){
	
	init();

	SifInitRpc(0);
	FlushCache(0);
	FlushCache(2);
	LoadExecPS2("rom0:OSDSYS", 0, NULL);
    
    return 0;
}
