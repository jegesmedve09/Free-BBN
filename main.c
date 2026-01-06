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
#include "utils.h"
#include "settings.h"
#include "pad.h"


#include "splash.h"
#include "menu.h"

void init(void){
	SifInitRpc(0);
    while (!SifIopReset("", 0)) {};
    while (!SifIopSync()) {};
    SifInitRpc(0);
	

	//audio
    SifLoadModule("rom0:LIBSD", 0, NULL);
    SifLoadModule(DEVICE ":/audsrv.irx", 0, NULL);
    
    //controller
    SifLoadModule("rom0:SIO2MAN", 0, NULL);
    SifLoadModule("rom0:PADMAN", 0, NULL);
    
    //Storage
    SifLoadModule("rom0:MCMAN", 0, NULL);
    SifLoadModule("rom0:MCSERV", 0, NULL);
    SifLoadModule("rom0:USBD", 0, NULL);
	//SifLoadModule("rom0:USBHDFSD", 0, NULL);
    FuckAroundSilentlyMs(1000);
    
    pad_init();
	
    gfx_init();
    gfx_clear(GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x80, 0x00));
    gfx_flip();
    
    
	//pad_init();
	
    //sound_init();
}

int main(void){
	
	init();
	
    splash_show();
    
    menu_show();

    while (1)
    {
		//gfx_exec();
        //gfx_flip();
    }

    return 0;
}

