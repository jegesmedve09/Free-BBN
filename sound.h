
#ifndef SOUND_H
#define SOUND_H

int sound_init(void);
int sound_stop(void);
int sound_start(const char* file_path);
int sound_update(void);

#endif
