#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <iopcontrol.h>
#include <loadfile.h>
#include <libcdvd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sbv_patches.h>

#include <sys/stat.h>
#define GS_BGCOLOR ((volatile u64*)0x120000e0)   // if not already
void FuckAroundSilentlyMs(int miliseconds)
{
    unsigned int start, now;

    __asm__ volatile("mfc0 %0, $9" : "=r"(start));

    while (1)
    {
        __asm__ volatile("mfc0 %0, $9" : "=r"(now));
        if ((now - start) >= (unsigned int)(miliseconds * 147456))
            break;
    }
}




int main(void)
{
    while (1)
    {
    *GS_BGCOLOR = 0xFFFFFF;
    FuckAroundSilentlyMs(1000);
	
    *GS_BGCOLOR = 0x000000;
    FuckAroundSilentlyMs(1000);
	}
}
