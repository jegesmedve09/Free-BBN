#include <tamtypes.h>
#include <sys/stat.h>

#ifndef UTILS_H
#define UTILS_H

#define DEV_EXIST(path) (stat(path, &(struct stat){0}) == 0)

void FuckAroundSilently(int frames);        // Wait N frames (50 for ~1s on PAL)
void FuckAroundSilentlyMs(int milliseconds); // Wait N ms
int get_random_in_range(int from, int to);

#endif
