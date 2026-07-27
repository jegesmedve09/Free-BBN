#ifndef AUDIO_H
#define AUDIO_H

#include <tamtypes.h>
#include <stdio.h>

#define AUDIO_FEED_CHUNK 8192 //32768//8192   // bytes per mix/feed cycle
#define MAX_VOICES 5			 // how many WAVs can play simultaneously

typedef struct {
	FILE *f;
	u32 data_start;
	u32 data_size;
	u32 bytes_read;
	int loop;
	int active;	  // currently contributing to the mix
	int in_use;	   // slot occupied at all (file open)
} AudioVoice;

int  audio_init(void);
int  audio_voice_open(int index, const char *path, int loop); // load + arm a voice slot
void audio_voice_play(int index);							  // (re)start playback from data_start
void audio_voice_stop(int index);
void audio_mixer_update(void);   // call once per frame — mixes all active voices, feeds audsrv
void audio_voice_pause(int index);
void audio_voice_resume(int index);
void audio_quit(void);

#endif
