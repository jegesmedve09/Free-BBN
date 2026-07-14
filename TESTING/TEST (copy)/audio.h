#ifndef AUDIO_H
#define AUDIO_H

#include <tamtypes.h>
#include <stdio.h>

#define AUDIO_FEED_CHUNK 8192   // bytes fed to audsrv per update() call, tune later

typedef struct {
    FILE *f;
    u32 data_start;
    u32 data_size;
    u32 bytes_read;
    int loop;
    int playing;
    int channels;
    int sample_rate;
    int bits;
    u8  feed_buf[AUDIO_FEED_CHUNK]; // reused every frame, no malloc churn
} AudioStream;

extern AudioStream snd_menu;
extern AudioStream snd_select;
extern AudioStream snd_back;
extern AudioStream snd_custom0;
extern AudioStream snd_custom1;

int  audio_init(void);
int  audio_stream_open(AudioStream *s, const char *path, int loop);
void audio_stream_update(AudioStream *s);
void audio_stream_stop(AudioStream *s);
void audio_stream_close(AudioStream *s);
void audio_quit(void);

#endif
