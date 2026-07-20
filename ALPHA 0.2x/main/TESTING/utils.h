#include <tamtypes.h>
#include <sys/stat.h>

#ifndef UTILS_H
#define UTILS_H

#define DEV_EXIST(path) (stat(path, &(struct stat){0}) == 0)

void FuckAroundSilently(int frames);
void FuckAroundSilentlyMs(int milliseconds);
int get_random_in_range(int from, int to);
char *path_portableinator(const char *path);
#endif
