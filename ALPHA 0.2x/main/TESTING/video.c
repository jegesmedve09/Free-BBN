#include "video.h"
#include "gfx.h"
#include "libmpeg.h"
#include "debug.h"
#include "utils.h"

#include <dma_tags.h>
#include <gif_tags.h>
#include <gs_psm.h>
#include <gs_gp.h>

#include <kernel.h>
#include <dma.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <gsKit.h>

#define CHUNK_SIZE (2048 * 32) // 64KB, keep whatever you last tuned this to
#define SRC_FPS 60

#define VID_MAX_W  640
#define VID_MAX_H  512
#define VID_MAX_BYTES (VID_MAX_W * VID_MAX_H * 4)

#define ROUND_UP_16(x) (((x) + 15) & ~15)

typedef enum { V_STOPPED, V_PLAYING, V_PAUSED } VideoState;

typedef struct {
    MPEGSequenceInfo *m_pInfo;
    void *m_pData;
} InitCBParam;

static VideoState s_state = V_STOPPED;
static int s_fd = -1;
static s64 s_curPTS;
static InitCBParam s_cb;
static GSTEXTURE s_tex;
static int s_dmaReady = 0;
static int s_isPAL = 0;
static int s_accum = 0;

static char s_path[256];
static int s_loop = 0;

static unsigned char *s_chunk = NULL;

static u8 *s_rasterBuf  = NULL;
static u8 *s_decodeBuf  = NULL;
static u32 s_texVram    = 0;
static int s_vramReady  = 0;

static int SetDMA(void *apUserData);
static void *InitCB(void *apParam, MPEGSequenceInfo *apInfo);
static void restart_stream(void);

// --- buffered logging: collect in RAM, write once, so logging itself
//     never adds I/O contention while we're trying to measure timing ---
#define LOG_BUF_LINES 128
static char s_logBuf[LOG_BUF_LINES][128];
static int  s_logCount = 0;

static void buffered_log(const char *fmt, ...)
{
    if (s_logCount >= LOG_BUF_LINES) return;
    va_list args;
    va_start(args, fmt);
    vsnprintf(s_logBuf[s_logCount], sizeof(s_logBuf[0]), fmt, args);
    va_end(args);
    s_logCount++;
}

static void flush_log(void)
{
    for (int i = 0; i < s_logCount; i++) dbg_log("%s", s_logBuf[i]);
    s_logCount = 0;
}

void video_init(void)
{
    if (s_dmaReady) return;

    dma_channel_initialize(DMA_CHANNEL_toIPU, NULL, 0);
    memset(&s_tex, 0, sizeof(s_tex));
    s_isPAL = !(*(volatile u8*)PAL_NTSC);

    s_chunk     = memalign(64, CHUNK_SIZE);
    s_decodeBuf = memalign(64, VID_MAX_BYTES);
    s_rasterBuf = memalign(64, VID_MAX_BYTES);
    s_texVram   = gsKit_vram_alloc(gsGlobal,
                      gsKit_texture_size(VID_MAX_W, VID_MAX_H, GS_PSM_32),
                      GSKIT_ALLOC_USERBUFFER);

    s_vramReady = (s_chunk && s_decodeBuf && s_rasterBuf && s_texVram != 0);
    dbg_log("video_init: chunk=%p decodeBuf=%p rasterBuf=%p vram=0x%08x ready=%d isPAL=%d\n",
            s_chunk, s_decodeBuf, s_rasterBuf, s_texVram, s_vramReady, s_isPAL);

    s_dmaReady = 1;
}

int video_play(const char *path, int loop)
{
    if (!s_vramReady) { dbg_log("video_play: not initialized\n"); return -1; }
    if (!path || !*path) return -1;

    video_exit();

    strncpy(s_path, path, sizeof(s_path) - 1);
    s_path[sizeof(s_path) - 1] = '\0';
    s_loop = loop;
    s_accum = 0;
    s_logCount = 0; // fresh log window for this playback session

    s_fd = open(path, O_RDONLY);
    dbg_log("video_play: open('%s') = %d, loop=%d\n", path, s_fd, loop);
    if (s_fd < 0) { s_state = V_STOPPED; return -1; }

    memset(&s_cb, 0, sizeof(s_cb));
    MPEG_Initialize(SetDMA, NULL, InitCB, &s_cb, &s_curPTS);

    s_state = V_PLAYING;
    return 0;
}

static void restart_stream(void)
{
    dma_channel_wait(DMA_CHANNEL_toIPU, 0);
    MPEG_Destroy();

    s_cb.m_pData = NULL;
    if (s_fd >= 0) { close(s_fd); s_fd = -1; }

    s_fd = open(s_path, O_RDONLY);
    if (s_fd < 0) { s_state = V_STOPPED; return; }

    memset(&s_cb, 0, sizeof(s_cb));
    MPEG_Initialize(SetDMA, NULL, InitCB, &s_cb, &s_curPTS);
}

void video_pause(void)  { if (s_state == V_PLAYING) s_state = V_PAUSED; }
void video_resume(void) { if (s_state == V_PAUSED)  s_state = V_PLAYING; }
int  video_is_playing(void) { return s_state == V_PLAYING; }

int video_update(void)
{
    if (s_state != V_PLAYING) return 0;

    int target = s_isPAL ? 50 : 60;
    s_accum += SRC_FPS;

    int decoded_any = 0;
    while (s_accum >= target) {
        unsigned int td0 = read_count();
        s64 pts;
        int ok = MPEG_Picture(s_cb.m_pData, &pts);
        unsigned int td1 = read_count();

        static int dn = 0;
        if (dn < 30) {
            buffered_log("decode=%uus\n", (td1 - td0) * 1000 / 147456);
            dn++;
        }

        s_accum -= target;

        if (!ok) {
            if (s_loop) { restart_stream(); s_accum = 0; flush_log(); return 0; }
            video_exit();
            flush_log();
            return 1;
        }
        decoded_any = 1;
    }

    if (!decoded_any) return 0;

    unsigned int t0 = read_count();

    int mbw = ROUND_UP_16(s_tex.Width)  >> 4;
    int mbh = ROUND_UP_16(s_tex.Height) >> 4;

    u8 *src = (u8*)s_cb.m_pData;
    for (int by = 0; by < mbh; by++) {
        u8 *dstRowBase = s_rasterBuf + (by*16) * s_tex.Width * 4;
        for (int bx = 0; bx < mbw; bx++) {
            u8 *dst = dstRowBase + bx*16*4;
            for (int row = 0; row < 16; row++) {
                memcpy(dst, src, 64);
                dst += s_tex.Width * 4;
                src += 64;
            }
        }
    }

    unsigned int t1 = read_count();

    SyncDCache(s_rasterBuf, s_rasterBuf + s_tex.Width * s_tex.Height * 4);
    s_tex.Mem = (u32*)s_rasterBuf;
    gsKit_texture_upload(gsGlobal, &s_tex);

    unsigned int t2 = read_count();

    gsGlobal->PrimAlphaEnable = GS_SETTING_OFF;
    gsKit_prim_sprite_texture(gsGlobal, &s_tex,
        0, 0, 0, 0,
        gsGlobal->Width, gsGlobal->Height,
        s_tex.Width, s_tex.Height,
        1, 0x80808080);
    gsGlobal->PrimAlphaEnable = GS_SETTING_ON;

    unsigned int t3 = read_count();
    unsigned int total_us = (t3 - t0) * 1000 / 147456;

    // visual budget indicator - green if under NTSC budget, red if over
    *(volatile u64*)0x120000e0 = (total_us < 16700) ? 0x00FF00 : 0xFF0000;
    static int n = 0;
    if (n < 30) {
        unsigned int untile_us = (t1 - t0) * 1000 / 147456;
        unsigned int upload_us = (t2 - t1) * 1000 / 147456;
        unsigned int draw_us   = (t3 - t2) * 1000 / 147456;
        dbg_log("untile=%uus upload=%uus draw=%uus\n", untile_us, upload_us, draw_us);
        n++;
        if (n == 30) flush_log(); // dump everything once we've got a good sample
    }

    return 0;
}

void video_exit(void)
{
    if (s_state == V_STOPPED && s_fd < 0) return;

    dma_channel_wait(DMA_CHANNEL_toIPU, 0);
    MPEG_Destroy();

    s_cb.m_pData = NULL;
    if (s_fd >= 0) { close(s_fd); s_fd = -1; }
    s_state = V_STOPPED;
}

static int SetDMA(void *apUserData)
{
    (void)apUserData;
    memset(s_chunk, 0, CHUNK_SIZE);
    int n = read(s_fd, s_chunk, CHUNK_SIZE);
    if (n <= 0) return 0;

    SyncDCache(s_chunk, s_chunk + CHUNK_SIZE);
    dma_channel_wait(DMA_CHANNEL_toIPU, 0);
    dma_channel_send_normal(DMA_CHANNEL_toIPU, s_chunk, CHUNK_SIZE >> 4, 0, 0);
    return 1;
}

static void *InitCB(void *apParam, MPEGSequenceInfo *apInfo)
{
    InitCBParam *lp = (InitCBParam *)apParam;

    int codedW = ROUND_UP_16(apInfo->m_Width);
    int codedH = ROUND_UP_16(apInfo->m_Height);

    if (codedW > VID_MAX_W || codedH > VID_MAX_H) {
        buffered_log("InitCB: REFUSED %dx%d (coded %dx%d) > max %dx%d\n",
                      apInfo->m_Width, apInfo->m_Height, codedW, codedH, VID_MAX_W, VID_MAX_H);
    }

    buffered_log("InitCB: sequence %dx%d (coded %dx%d)\n",
                  apInfo->m_Width, apInfo->m_Height, codedW, codedH);

    lp->m_pData = s_decodeBuf;
    lp->m_pInfo = apInfo;
    SyncDCache(s_decodeBuf, s_decodeBuf + VID_MAX_BYTES);

    s_tex.Width  = apInfo->m_Width;   // display size, unchanged - what gets shown
    s_tex.Height = apInfo->m_Height;
    s_tex.PSM    = GS_PSM_32;
    s_tex.Filter = GS_FILTER_NEAREST;
    s_tex.Mem    = (u32 *)s_decodeBuf;
    s_tex.Vram   = s_texVram;

    return s_decodeBuf;
}
