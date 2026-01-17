#ifndef UTILS_H
#define UTILS_H

void FuckAroundSilently(int frames);        // Wait N frames (50 for ~1s on PAL)
void FuckAroundSilentlyMs(int milliseconds); // Wait N ms
int get_random_in_range(int from, int to);
void PowerOff(void);
#endif
