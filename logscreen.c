#include "gfx.h"  // For gfx_draw_text
#include <tamtypes.h>  // For u64
#include <string.h>    // For strcpy and strncpy

#define MAX_LOG_LINES 15      // Adjust based on screen space (e.g., for 512 height, assuming ~30px per line)
#define MAX_LOG_LENGTH 128    // Max length per log message, adjust as needed

static char log_lines[MAX_LOG_LINES][MAX_LOG_LENGTH];
static int log_count = 0;

int xpos,ypos,lineheight, charscale, charspacing;
u64 charcolor;

void logscreen_init(int x, int y, int line_height, u64 color, int scale, int spacing) {
    log_count = 0;
    // Optionally zero out the array if needed
    memset(log_lines, 0, sizeof(log_lines));
    
    xpos=x;
    ypos=y;
    lineheight=line_height;
    charcolor=color;
    charscale=scale;
    charspacing=spacing;
}

void logscreen_draw(void) {
    for (int i = 0; i < log_count; i++) {
        int line_y = ypos + i * lineheight;
        gfx_draw_text(log_lines[i], xpos, line_y, charcolor, charscale, charspacing);
    }
}

void logscreen_add(const char* msg) {
    if (log_count < MAX_LOG_LINES) {
        // Add to the end if not full
        strncpy(log_lines[log_count], msg, MAX_LOG_LENGTH - 1);
        log_lines[log_count][MAX_LOG_LENGTH - 1] = '\0';
        log_count++;
    } else {
        // Shift all lines up (oldest disappears)
        for (int i = 0; i < MAX_LOG_LINES - 1; i++) {
            strcpy(log_lines[i], log_lines[i + 1]);
        }
        // Add new at the bottom
        strncpy(log_lines[MAX_LOG_LINES - 1], msg, MAX_LOG_LENGTH - 1);
        log_lines[MAX_LOG_LINES - 1][MAX_LOG_LENGTH - 1] = '\0';
    }
}

void logscreen_add_draw(const char* msg) {
    if (log_count < MAX_LOG_LINES) {
        // Add to the end if not full
        strncpy(log_lines[log_count], msg, MAX_LOG_LENGTH - 1);
        log_lines[log_count][MAX_LOG_LENGTH - 1] = '\0';
        log_count++;
    } else {
        // Shift all lines up (oldest disappears)
        for (int i = 0; i < MAX_LOG_LINES - 1; i++) {
            strcpy(log_lines[i], log_lines[i + 1]);
        }
        // Add new at the bottom
        strncpy(log_lines[MAX_LOG_LINES - 1], msg, MAX_LOG_LENGTH - 1);
        log_lines[MAX_LOG_LINES - 1][MAX_LOG_LENGTH - 1] = '\0';
    }
    logscreen_draw();
}
