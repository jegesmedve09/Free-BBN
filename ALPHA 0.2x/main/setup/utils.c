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

#define PORTABLE_ADDRESS    0x01EFF800

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
    if (from > to)
    {
        int temp = from;
        from = to;
        to = temp;
    }

    u32 entropy = 0;

    u32 count;
    __asm__ volatile ("mfc0 %0, $9" : "=r"(count));
    entropy ^= count;
    __asm__ volatile ("mfc0 %0, $9" : "=r"(count));
    entropy ^= (count << 13) | (count >> 19);
    __asm__ volatile ("mfc0 %0, $9" : "=r"(count));
    entropy ^= count ^ (count << 7) ^ (count >> 11);


    volatile u32 stack_ptr;
    __asm__ volatile ("move %0, $sp" : "=r"(stack_ptr));
    entropy ^= stack_ptr ^ (stack_ptr >> 8);


    entropy ^= (u32)(uintptr_t)&get_random_in_range;


    extern GSGLOBAL *gsGlobal;
    if (gsGlobal)
    {
        u64 csr = *GS_CSR;
        entropy ^= (u32)csr ^ (u32)(csr >> 32);
    }

    u64 timer = GetTimerSystemTime();
    entropy ^= (u32)timer ^ (u32)(timer >> 32);


    volatile u32 dummy = entropy & 0xFF;
    u32 loop_count = 0;
    for (volatile u32 i = 0; i < 128 + dummy; i++)
    {
        loop_count += i ^ entropy;
    }
    entropy ^= loop_count ^ (loop_count << 5) ^ (loop_count >> 17);

    u32 x = entropy;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;

    __asm__ volatile ("mfc0 %0, $9" : "=r"(count));
    x ^= count;

    if (x == 0) x = 0x80000001;

    u32 range = (u32)(to - from + 1);
    return from + (int)(x % range);
}

char *path_portableinator(const char *path)
{
    static char result[2048];

    strncpy(result, (char*)PORTABLE_ADDRESS, sizeof(result) - 1);
    result[sizeof(result) - 1] = '\0';
    strncat(result, path, sizeof(result) - strlen(result) - 1);
    result[sizeof(result) - 1] = '\0';
    return result;
}

