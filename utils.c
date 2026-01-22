#include "utils.h"

#include "gfx.h"

#include <kernel.h>
#include <sifrpc.h>
#include <iopcontrol.h>
#include <loadfile.h>
#include <iopheap.h>
#include <libpwroff.h>
#include <sbv_patches.h>
#include <stdint.h>
#include <timer.h>

#include "irx.h"
//GLORY FOR THE ORIGINAL FUCKED UP CODE, SHALL NEVER BE DELETED NOR BY HUMAN NOR BY ANY NON-HUMAN BRAINFUCKS

//void FuckAroundSilently(int frames)
//{
//    // Calibrated busy loop
//    // ~50 frames = 1 second on PAL (your 50007)
//    // Tested on real hardware + PCSX2
//    volatile int cycles = frames * 100000;  // Adjust multiplier if too fast/slow
//
//    while (cycles--)
//    {
//        // Fuck around silently
//        __asm__ ("nop");
//    }
//}
//void FuckAroundSilentlyMs(int milliseconds)
//{
//    // ~50000 cycles per millisecond on PS2 EE @ 294MHz
//    volatile int cycles = milliseconds * 50000;
//
//    while (cycles--)
//    {
//        __asm__ ("nop");
//    }
//}

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


int get_random_in_range(int from, int to)
{
    if (from > to) {
        int temp = from;
        from = to;
        to = temp;
    }

    // ──────────────────────────────────────────────────────────────
    // Collect many different sources of entropy in 32-bit chunks
    // ──────────────────────────────────────────────────────────────

    u32 entropy = 0;

    // 1. Cycle counter multiple times + xor folding
    u32 count;
    __asm__ volatile ("mfc0 %0, $9" : "=r"(count));
    entropy ^= count;
    __asm__ volatile ("mfc0 %0, $9" : "=r"(count));
    entropy ^= (count << 13) | (count >> 19);
    __asm__ volatile ("mfc0 %0, $9" : "=r"(count));
    entropy ^= count ^ (count << 7) ^ (count >> 11);

    // 2. Stack address + some local variables (ASLR is weak but still something)
    volatile u32 stack_ptr;
    __asm__ volatile ("move %0, $sp" : "=r"(stack_ptr));
    entropy ^= stack_ptr ^ (stack_ptr >> 8);

    // 3. Current function address itself (code location)
    entropy ^= (u32)(uintptr_t)&get_random_in_range;

    // 4. GS CSR register if gsGlobal is already initialized
    extern GSGLOBAL *gsGlobal; // assuming you have this global
    if (gsGlobal) {
        u64 csr = *GS_CSR;
        entropy ^= (u32)csr ^ (u32)(csr >> 32);
    }

    // 5. Timer / system time (if initialized)
    u64 timer = GetTimerSystemTime();  // 1us ticks usually
    entropy ^= (u32)timer ^ (u32)(timer >> 32);

    // 6. Small busy-wait loop whose duration is slightly unpredictable
    //    (branch prediction, cache effects, memory bus contention)
    volatile u32 dummy = entropy & 0xFF;
    u32 loop_count = 0;
    for (volatile u32 i = 0; i < 128 + dummy; i++) {
        loop_count += i ^ entropy;
    }
    entropy ^= loop_count ^ (loop_count << 5) ^ (loop_count >> 17);

    // 7. Xorshift32 final mixing step (very fast avalanche)
    u32 x = entropy;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;

    // 8. Last tiny bit of paranoia - read count one more time
    __asm__ volatile ("mfc0 %0, $9" : "=r"(count));
    x ^= count;

    // Final number is never zero (xorshift hates zero state)
    if (x == 0) x = 0x80000001;

    // Scale to requested range
    // (simple but biased - good enough for graphics/noise/particles)
    u32 range = (u32)(to - from + 1);
    return from + (int)(x % range);
}


void PowerOff(void)
{  	
	SifInitRpc(0);
	SifIopReset("", 0);
	while(!SifIopSync());

	SifInitRpc(0);
	SifLoadFileInit();
	SifInitIopHeap();
	sbv_patch_enable_lmb();

	SifExecModuleBuffer(irx_poweroff, irx_poweroff_size, 0, NULL, NULL);
	poweroffInit();
	poweroffShutdown();

	SifExitRpc();	
}



#include <kernel.h>
#include <sifrpc.h>
#include <libcdvd.h>
#include <loadfile.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define SYSTEM_CNF_PATH "cdrom0:\\SYSTEM.CNF;1"
#define MAX_CNF_SIZE   2048

static void wait_for_disc(void)
{
    int type;

    /* Wait for disc insertion */
    do {
        type = CdGetDiskType();
        FuckAroundSilentlyMs(100);
    } while (type == CDVD_TYPE_NODISK);

    /* Wait until drive becomes ready */
    while (!cdDiskReady(0))
        FuckAroundSilentlyMs(100);
}


static int parse_boot2(char *cnf, char *out_path)
{
    char *p = strstr(cnf, "BOOT2");
    if (!p)
        return -1;

    p = strchr(p, '=');
    if (!p)
        return -1;

    p++; // skip '='
    while (*p == ' ')
        p++;

    strcpy(out_path, p);

    // Trim newline
    char *e = strchr(out_path, '\r');
    if (e) *e = 0;
    e = strchr(out_path, '\n');
    if (e) *e = 0;

    return 0;
}

void launch_dvd_game(void)
{
    char cnf[MAX_CNF_SIZE];
    char boot_path[256];
    int fd;

    SifInitRpc(0);
    cdInit(CDVD_INIT_INIT);


    wait_for_disc();

    fd = open(SYSTEM_CNF_PATH, O_RDONLY);
    if (fd < 0)
        return;

    memset(cnf, 0, sizeof(cnf));
    read(fd, cnf, sizeof(cnf) - 1);
    close(fd);

    if (parse_boot2(cnf, boot_path) < 0)
        return;

    // BOOT2 usually looks like: cdrom0:\SLUS_203.12;1
    FlushCache(0);
    FlushCache(2);

    LoadExecPS2(boot_path, 0, NULL);
}


u8 dec_to_bcd(u8 dec) { return ((dec / 10) << 4) | (dec % 10); }

u8 bcd_to_dec(u8 bcd) { return (bcd   >> 4) * 10 + (bcd   & 0x0F); }
