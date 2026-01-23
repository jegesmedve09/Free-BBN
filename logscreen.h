
#ifndef LOGSCREEN_H
#define LOGSCREEN_H

void logscreen_init(int x, int y, int line_height, u64 color, int scale, int spacing);
void logscreen_draw(void);
void logscreen_add(const char* msg);
void logscreen_add_draw(const char* msg);

#endif
