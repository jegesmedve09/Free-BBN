#include <tamtypes.h>
#include <sys/stat.h>

#ifndef UTILS_H
#define UTILS_H

#define DEV_EXIST(path) (stat(path, &(struct stat){0}) == 0)

void FuckAroundSilently(int frames);        // Wait N frames (50 for ~1s on PAL)
void FuckAroundSilentlyMs(int milliseconds); // Wait N ms
void launch_dvd_game();
int get_random_in_range(int from, int to);
void PowerOff(void);

u8 bcd_to_dec(u8 bcd);
u8 dec_to_bcd(u8 dec);
float char_to_float(const char *str, float def);
u8 char_to_u8(const char *str, u8 def);

#endif
