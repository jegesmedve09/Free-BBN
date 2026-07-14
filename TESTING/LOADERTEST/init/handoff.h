#ifndef HANDOFF_H
#define HANDOFF_H
#include <tamtypes.h>

#define HANDOFF_ADDR   0x01FE0000   // fixed, inside the reserved top region
#define HANDOFF_MAGIC  0xF00DCAFE

typedef struct {
    u32 magic;

    // --- request: what should the loader load next ---
    char path[256];      // e.g. "host:/MAIN.ELF" or "mass:/VIDEO_PLAYER.ELF"

    // --- GS software state (gsKit's bookkeeping, not hardware) ---
    int  gs_ready;
    int  Mode, Interlace, Field, Width, Height, PSM;
    u32  FrameBuffer;
    u32  vram_watermark;   // gsGlobal->CurrentPointer

    // --- IOP/audio ---
    u32  iop_ready;
} HandoffInfo;

static inline HandoffInfo* handoff(void) {
    return (HandoffInfo*)HANDOFF_ADDR;
}

#endif
