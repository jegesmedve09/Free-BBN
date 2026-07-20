#include <tamtypes.h>
#include <sys/stat.h>

#ifndef UTILS_H
#define UTILS_H

#define DEV_EXIST(path) (stat(path, &(struct stat){0}) == 0)

#define SHARED_BASE_ADDR    0x01EFF7F0

#define INTERLACED          (SHARED_BASE_ADDR + 0x00)
#define PAL_NTSC            (SHARED_BASE_ADDR + 0x01)
#define PRIM_ALPHA          (SHARED_BASE_ADDR + 0x02)
#define HAS_TO_BE_TRUE      (SHARED_BASE_ADDR + 0x03)
#define GS_WIDTH            (SHARED_BASE_ADDR + 0x04)
#define GS_HEIGHT           (SHARED_BASE_ADDR + 0x08)

void FuckAroundSilently(int frames);
void FuckAroundSilentlyMs(int milliseconds);
int get_random_in_range(int from, int to);
char *path_portableinator(const char *path);
#endif
