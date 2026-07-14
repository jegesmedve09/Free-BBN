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
#include <sys/stat.h>
#include <kernel.h>
#include <sifrpc.h>
#include <libcdvd.h>
#include <loadfile.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


#define DEV_EXIST(path) (stat(path, &(struct stat){0}) == 0)
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
