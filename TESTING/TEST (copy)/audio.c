#include "audio.h"
#include <audsrv.h>
#include <string.h>

AudioStream snd_menu;
AudioStream snd_select;
AudioStream snd_back;
AudioStream snd_custom0;
AudioStream snd_custom1;


int audio_init(void)
{
    int ret = audsrv_init();
    if (ret != 0) {
        printf("audsrv_init failed, code %d\n", ret);
        return -1;
    }
    return 0;
}

int audio_stream_open(AudioStream *s, const char *path, int loop)
{
    memset(s, 0, sizeof(AudioStream));
    s->f = fopen(path, "rb");
    if (!s->f) { printf("audio: cannot open %s\n", path); return -1; }

    char tag[4];
    u32 chunk_size;
    u16 format_tag = 0, channels = 0, bits = 0;
    u32 sample_rate = 0;

    fread(tag, 1, 4, s->f);
    if (memcmp(tag, "RIFF", 4)) { fclose(s->f); return -2; }
    fseek(s->f, 4, SEEK_CUR);
    fread(tag, 1, 4, s->f);
    if (memcmp(tag, "WAVE", 4)) { fclose(s->f); return -3; }

    int found_fmt = 0, found_data = 0;
    while (fread(tag, 1, 4, s->f) == 4) {
        if (fread(&chunk_size, 4, 1, s->f) != 1) break;

        if (!memcmp(tag, "fmt ", 4)) {
            fread(&format_tag, 2, 1, s->f);
            fread(&channels, 2, 1, s->f);
            fread(&sample_rate, 4, 1, s->f);
            fseek(s->f, 6, SEEK_CUR);
            fread(&bits, 2, 1, s->f);
            long extra = chunk_size - 16;
            if (extra > 0) fseek(s->f, extra, SEEK_CUR);
            found_fmt = 1;
        }
        else if (!memcmp(tag, "data", 4)) {
            s->data_start = ftell(s->f);
            s->data_size = chunk_size;
            found_data = 1;
            break;
        }
        else {
            fseek(s->f, chunk_size, SEEK_CUR);
            if (chunk_size & 1) fseek(s->f, 1, SEEK_CUR);
        }
    }

    if (!found_fmt || !found_data) {
        printf("audio: missing fmt/data chunk in %s\n", path);
        fclose(s->f);
        return -4;
    }

    s->channels = channels;
    s->sample_rate = sample_rate;
    s->bits = bits;
    s->loop = loop;
    s->bytes_read = 0;

    struct audsrv_fmt_t fmt;
    fmt.bits = bits;
    fmt.channels = channels;
    fmt.freq = sample_rate;

    int ret = audsrv_set_format(&fmt);
    if (ret != 0) {
        printf("audsrv_set_format failed, code %d\n", ret);
        fclose(s->f);
        return -5;
    }

    audsrv_set_volume(MAX_VOLUME);

    s->playing = 1;
    printf("audio: opened %s (%dHz, %dch, %dbit), %lu bytes PCM\n",
           path, s->sample_rate, s->channels, s->bits, (unsigned long)s->data_size);
    return 0;
}

// call every frame from your main loop. Non-blocking: only feeds if
// audsrv's ring buffer actually has room, otherwise returns immediately.
void audio_stream_update(AudioStream *s)
{
    if (!s->playing) return;

    int avail = audsrv_available(); // bytes free in audsrv's ring buffer
    if (avail < AUDIO_FEED_CHUNK) return; // not full-frame-worth of room yet, skip

    u32 remain = (s->data_size > s->bytes_read) ? (s->data_size - s->bytes_read) : 0;
    u32 to_read = (remain < AUDIO_FEED_CHUNK) ? remain : AUDIO_FEED_CHUNK;

    if (to_read > 0) {
        fread(s->feed_buf, 1, to_read, s->f);
        s->bytes_read += to_read;
        audsrv_play_audio((char *)s->feed_buf, to_read);
    }

    if (to_read < AUDIO_FEED_CHUNK) {
        if (s->loop) {
            fseek(s->f, s->data_start, SEEK_SET);
            s->bytes_read = 0;
        } else {
            s->playing = 0;
        }
    }
}

void audio_stream_stop(AudioStream *s)
{
    audsrv_stop_audio();
    s->playing = 0;
}

void audio_stream_close(AudioStream *s)
{
    if (s->f) fclose(s->f);
}

void audio_quit(void)
{
    audsrv_quit();
}
