#include "audio.h"
#include <tamtypes.h>
#include <kernel.h>
#include <audsrv.h>
#include <string.h>
#include <malloc.h>

AudioVoice voices[MAX_VOICES];

// ---------------------------------------------------------------------
// Voice 0 is the single MUSIC voice — always streamed from disk, exactly
// like before. Voices 1..MAX_VOICES-1 are SFX voices — each one gets its
// own fixed 256KB RAM buffer, filled once at open time, so the mixer never
// touches disk for them and two SFX (or an SFX + music) can play at once
// without the USB stalls that were causing the glitching.
//
// This storage is kept file-scope here instead of added to AudioVoice in
// audio.h, so the whole fix stays contained to this file. NOTE: MAX_VOICES
// needs to be 5 in audio.h for this to give you 4 SFX slots (0=music,
// 1-4=SFX) — see the note at the bottom of this file.
// ---------------------------------------------------------------------
#define MUSIC_VOICE   0
#define SFX_SLOT_SIZE (256 * 1024)

static u8  *sfx_buf[MAX_VOICES];   // [MUSIC_VOICE] unused, stays NULL
static u32  sfx_size[MAX_VOICES];  // actual bytes loaded, <= SFX_SLOT_SIZE
static u32  sfx_pos[MAX_VOICES];   // read cursor into sfx_buf[i]

int audio_init(void)
{
	int ret = audsrv_init();
	if (ret != 0) {
		printf("audsrv_init failed, code %d\n", ret);
		return -1;
	}

	// fixed format for all assets — locked in since everything you're using
	// is already 16-bit/48000/stereo, so no per-voice resampling is needed
	struct audsrv_fmt_t fmt;
	fmt.bits = 16;
	fmt.channels = 2;
	fmt.freq = 48000;

	ret = audsrv_set_format(&fmt);
	if (ret != 0) {
		printf("audsrv_set_format failed, code %d\n", ret);
		return -2;
	}
	audsrv_set_volume(MAX_VOLUME);

	memset(voices, 0, sizeof(voices));
	memset(sfx_buf, 0, sizeof(sfx_buf));
	memset(sfx_size, 0, sizeof(sfx_size));
	memset(sfx_pos, 0, sizeof(sfx_pos));
	return 0;
}

int audio_voice_open(int index, const char *path, int loop)
{
	if (index < 0 || index >= MAX_VOICES) return -1;

	AudioVoice *v = &voices[index];

	// Reopening a slot that already has an SFX buffer or open file? Free/close
	// the old one first so we don't leak.
	if (sfx_buf[index]) {
		free(sfx_buf[index]);
		sfx_buf[index] = NULL;
		sfx_size[index] = 0;
		sfx_pos[index] = 0;
	}
	if (v->f) {
		fclose(v->f);
	}
	memset(v, 0, sizeof(AudioVoice));

	v->f = fopen(path, "rb");
	if (!v->f) { printf("audio: cannot open %s\n", path); return -2; }

	char tag[4];
	u32 chunk_size;
	u16 format_tag = 0, channels = 0, bits = 0;
	u32 sample_rate = 0;

	fread(tag, 1, 4, v->f);
	if (memcmp(tag, "RIFF", 4)) { fclose(v->f); v->f = NULL; return -3; }
	fseek(v->f, 4, SEEK_CUR);
	fread(tag, 1, 4, v->f);
	if (memcmp(tag, "WAVE", 4)) { fclose(v->f); v->f = NULL; return -4; }

	int found_fmt = 0, found_data = 0;
	while (fread(tag, 1, 4, v->f) == 4) {
		if (fread(&chunk_size, 4, 1, v->f) != 1) break;

		if (!memcmp(tag, "fmt ", 4)) {
			fread(&format_tag, 2, 1, v->f);
			fread(&channels, 2, 1, v->f);
			fread(&sample_rate, 4, 1, v->f);
			fseek(v->f, 6, SEEK_CUR);
			fread(&bits, 2, 1, v->f);
			long extra = chunk_size - 16;
			if (extra > 0) fseek(v->f, extra, SEEK_CUR);
			found_fmt = 1;
		}
		else if (!memcmp(tag, "data", 4)) {
			v->data_start = ftell(v->f);
			v->data_size = chunk_size;
			found_data = 1;
			break;
		}
		else {
			fseek(v->f, chunk_size, SEEK_CUR);
			if (chunk_size & 1) fseek(v->f, 1, SEEK_CUR);
		}
	}

	if (!found_fmt || !found_data) {
		printf("audio: missing fmt/data in %s\n", path);
		fclose(v->f); v->f = NULL; return -5;
	}
	if (channels != 2 || sample_rate != 48000 || bits != 16) {
		printf("audio: %s is %dHz %dch %dbit, need 48000/2/16\n",
			   path, sample_rate, channels, bits);
		fclose(v->f); v->f = NULL; return -6;
	}

	v->loop = loop;
	v->bytes_read = 0;
	v->in_use = 1;
	v->active = 0;   // starts playing immediately once opened; call audio_voice_stop() to silence

	if (index == MUSIC_VOICE) {
		// MUSIC voice: keep streaming exactly like before.
		printf("audio: voice %d (MUSIC) streaming %s\n", index, path);
		return 0;
	}

	// SFX voice: pull it fully into a fixed 256KB RAM slot right now.
	// Smaller files leave the tail unused; bigger ones get truncated to the
	// first SFX_SLOT_SIZE bytes (with a warning) — same fixed footprint no
	// matter what the file actually contains.
	sfx_buf[index] = malloc(SFX_SLOT_SIZE);
	if (!sfx_buf[index]) {
		printf("audio: SFX malloc failed for %s, voice %d disabled\n", path, index);
		fclose(v->f); v->f = NULL;
		v->in_use = 0;
		return -7;
	}

	fseek(v->f, v->data_start, SEEK_SET);
	u32 to_load = (v->data_size < SFX_SLOT_SIZE) ? v->data_size : SFX_SLOT_SIZE;
	u32 got = fread(sfx_buf[index], 1, to_load, v->f);
	sfx_size[index] = got;
	sfx_pos[index] = 0;

	if (v->data_size > SFX_SLOT_SIZE) {
		printf("audio: voice %d (%s) is %u bytes, SFX slot is %u — TRUNCATED\n",
			   index, path, v->data_size, (unsigned)SFX_SLOT_SIZE);
	}

	fclose(v->f);
	v->f = NULL;   // fully RAM-resident now, no file handle needed
	printf("audio: voice %d (SFX) preloaded %u/%u bytes into 256K slot (%s)\n",
		   index, sfx_size[index], v->data_size, path);
	return 0;
}

void audio_voice_play(int index)
{
	if (index < 0 || index >= MAX_VOICES) return;
	AudioVoice *v = &voices[index];
	if (!v->in_use) return;

	if (index == MUSIC_VOICE) {
		fseek(v->f, v->data_start, SEEK_SET);
		v->bytes_read = 0;
	} else {
		sfx_pos[index] = 0;
	}
	v->active = 1;
}

void audio_voice_stop(int index)
{
	if (index < 0 || index >= MAX_VOICES) return;
	voices[index].active = 0;
}

// mixes every active voice's next chunk into one buffer, feeds audsrv once
void audio_mixer_update(void)
{
    int avail = audsrv_available();
    if (avail < AUDIO_FEED_CHUNK) return;

    static s32 accum[AUDIO_FEED_CHUNK / 2] __attribute__((aligned(64)));
    static s16 temp[AUDIO_FEED_CHUNK / 2]  __attribute__((aligned(64)));
    static s16 out[AUDIO_FEED_CHUNK / 2]   __attribute__((aligned(64)));

    memset(accum, 0, sizeof(accum));
    int any_active = 0;

    for (int i = 0; i < MAX_VOICES; i++) {
        AudioVoice *v = &voices[i];
        if (!v->in_use || !v->active) continue;

        memset(temp, 0, AUDIO_FEED_CHUNK);
        u32 actually_read = 0;

        if (i == MUSIC_VOICE) {
            // MUSIC voice: the only one still allowed to touch disk.
            u32 remain = (v->data_size > v->bytes_read) ? (v->data_size - v->bytes_read) : 0;
            u32 to_read = (remain < AUDIO_FEED_CHUNK) ? remain : AUDIO_FEED_CHUNK;
            if (to_read > 0) {
                actually_read = fread(temp, 1, to_read, v->f);   // capture real return value
                v->bytes_read += actually_read;                    // advance by what REALLY happened
            }
        } else {
            // SFX voice: memcpy from its fixed RAM slot, no I/O, can't stall.
            u32 remain = (sfx_size[i] > sfx_pos[i]) ? (sfx_size[i] - sfx_pos[i]) : 0;
            u32 to_read = (remain < AUDIO_FEED_CHUNK) ? remain : AUDIO_FEED_CHUNK;
            if (to_read > 0) {
                memcpy(temp, sfx_buf[i] + sfx_pos[i], to_read);
                sfx_pos[i] += to_read;
                actually_read = to_read;
            }
        }

        int samples = AUDIO_FEED_CHUNK / 2;
        for (int s = 0; s < samples; s++) accum[s] += temp[s];
        any_active = 1;

        // treat a short read the same as hitting EOF/end-of-chunk, not as "fine, keep going"
        if (actually_read < AUDIO_FEED_CHUNK) {
            if (v->loop) {
                if (i == MUSIC_VOICE) {
                    fseek(v->f, v->data_start, SEEK_SET);
                    v->bytes_read = 0;
                } else {
                    sfx_pos[i] = 0;
                }
            } else {
                v->active = 0;
            }
        }
    }

    if (!any_active) return;

    for (int s = 0; s < AUDIO_FEED_CHUNK / 2; s++) {
        s32 v = accum[s];
        if (v > 32767) v = 32767;
        if (v < -32768) v = -32768;
        out[s] = (s16)v;
    }

    FlushCache(0);
    audsrv_play_audio((char *)out, AUDIO_FEED_CHUNK);
}

void audio_voice_pause(int index)
{
	voices[index].active = 0;
}

void audio_voice_resume(int index)
{
	voices[index].active = 1;
}

void audio_quit(void)
{
	for (int i = 0; i < MAX_VOICES; i++) {
		if (sfx_buf[i]) { free(sfx_buf[i]); sfx_buf[i] = NULL; }
		if (voices[i].f) { fclose(voices[i].f); voices[i].f = NULL; }
	}
	audsrv_quit();
}
