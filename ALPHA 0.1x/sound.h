#ifndef SOUND_H
#define SOUND_H

void sound_init(void);
void sound_stream_start(const char *filepath);
void sound_stream_update(void);  // call every frame
void sound_stream_stop(void);

#endif
