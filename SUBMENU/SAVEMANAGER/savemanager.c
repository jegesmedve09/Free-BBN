#include <tamtypes.h>
#include <kernel.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <libpad.h>
#include "gfx.h"
#include "menu.h"
#include "background.h"
#include "pad.h"
#include "utils.h"      // assuming you have this

#define MAX_MC          8
#define MAX_SAVES       48
#define ICONSYS_SIZE    964

// ──────────────────────────────────────────────
// Data structures
// ──────────────────────────────────────────────

static char mc_devices[MAX_MC][16];     // "mc0:/", "mc1:/", ...
static int mc_count = 0;

typedef struct {
    char folder_name[40];
    char game_title[132];
    char game_subtitle[100];
    int has_icon_sys;
} SaveEntry;

static SaveEntry save_entries[MAX_SAVES];
static int save_entry_count = 0;

// ──────────────────────────────────────────────
// Memory card detection
// ──────────────────────────────────────────────

static void detect_memory_cards(void) {
    mc_count = 0;
    for (int i = 0; i < MAX_MC; i++) {
        char path[16];
        snprintf(path, sizeof(path), "mc%d:/", i);
        if (DEV_EXIST(path)) {
            strncpy(mc_devices[mc_count], path, sizeof(mc_devices[0])-1);
            mc_devices[mc_count][sizeof(mc_devices[0])-1] = '\0';
            mc_count++;
        }
    }
}

// ──────────────────────────────────────────────
// Read title & subtitle from icon.sys
// ──────────────────────────────────────────────

static int read_icon_sys_info(const char *mc_path, const char *folder, SaveEntry *entry) {
    char path[256];
    snprintf(path, sizeof(path), "%s%s/icon.sys", mc_path, folder);

    FILE *f = fopen(path, "rb");
    if (!f) goto no_icon;

    char buffer[ICONSYS_SIZE];
    if (fread(buffer, 1, ICONSYS_SIZE, f) != ICONSYS_SIZE) {
        fclose(f);
        goto no_icon;
    }
    fclose(f);

    if (strncmp(buffer, "PS2D", 4) != 0) {
        goto no_icon;
    }

    // Title usually starts at 0xC0 (192)
    strncpy(entry->game_title, buffer + 192, sizeof(entry->game_title)-1);
    entry->game_title[sizeof(entry->game_title)-1] = '\0';

    // Look for newline to split subtitle
    char *newline = strchr(entry->game_title, '\n');
    if (newline) {
        *newline = '\0';
        strncpy(entry->game_subtitle, newline + 1, sizeof(entry->game_subtitle)-1);
        entry->game_subtitle[sizeof(entry->game_subtitle)-1] = '\0';
    } else {
        entry->game_subtitle[0] = '\0';
    }

    // Clean up trailing junk (very common in real saves)
    char *end = entry->game_subtitle + strlen(entry->game_subtitle) - 1;
    while (end >= entry->game_subtitle && (*end <= ' ' || *end == '\r')) {
        *end-- = '\0';
    }

    entry->has_icon_sys = 1;
    return 0;

no_icon:
    entry->has_icon_sys = 0;
    entry->game_title[0] = '\0';
    entry->game_subtitle[0] = '\0';
    return -1;
}

// ──────────────────────────────────────────────
// Load save folders from selected memory card
// ──────────────────────────────────────────────

static void load_save_folders(const char *mc_path) {
    save_entry_count = 0;

    DIR *dir = opendir(mc_path);
    if (!dir) return;

    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type != DT_DIR) continue;
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) continue;

        if (save_entry_count >= MAX_SAVES) break;

        SaveEntry *e = &save_entries[save_entry_count];
        strncpy(e->folder_name, ent->d_name, sizeof(e->folder_name)-1);
        e->folder_name[sizeof(e->folder_name)-1] = '\0';

        read_icon_sys_info(mc_path, ent->d_name, e);

        save_entry_count++;
    }
    closedir(dir);
}

// ──────────────────────────────────────────────
// Memory Card Selection Screen
// ──────────────────────────────────────────────

static int select_memory_card_screen(void) {
    detect_memory_cards();

    if (mc_count == 0) {
        gfx_fade_in(12);
        while (1) {
            background_update();
            gfx_draw_top_bar();
            gfx_draw_text("No memory cards detected", 100, 180,
                          GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0), 4, 2);
            gfx_draw_text("Press △ to return", 140, 240,
                          GS_SETREG_RGBAQ(0xAA,0xAA,0xAA,0x80,0), 3, 2);
            gfx_flip();
            gfx_exec();

            if (pad_get_pressed(0) & (PAD_TRIANGLE | PAD_CIRCLE)) {
                gfx_fade_out(12);
                return -1;
            }
        }
    }

    menu_reset_current_item();
    //menu_init(32, 255,220,100, 180,180,220, 3, 5, 4, 12, 3); // adjust to your taste

    gfx_fade_in(12);

    while (1) {
        background_update();
        gfx_draw_top_bar();

        gfx_draw_text("Select Memory Card", 60, 60,
                      GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0), 5, 3);

        const char *items[MAX_MC];
        for (int i = 0; i < mc_count; i++) {
            items[i] = mc_devices[i];
        }

        menu_draw(items, mc_count, 80, 140);

        gfx_flip();
        gfx_exec();

        u32 pressed = pad_get_pressed(0);

        if (pressed & PAD_DOWN)  menu_increment();
        if (pressed & PAD_UP)    menu_decrement();

        if (pressed & PAD_CROSS) {
            int chosen = menu_get_current_item();
            gfx_fade_out(12);
            return chosen;
        }
        if (pressed & PAD_TRIANGLE) {
            gfx_fade_out(12);
            return -1;
        }
    }
}

// ──────────────────────────────────────────────
// Save Folders Browser
// ──────────────────────────────────────────────

static void show_save_browser(int mc_index) {
    if (mc_index < 0 || mc_index >= mc_count) return;

    const char *mc = mc_devices[mc_index];
    load_save_folders(mc);

    menu_reset_current_item();
    // You can tweak these values to match your UI style
    //menu_init(36, 255,240,140, 200,200,255, 4, 5, 4, 10, 3);

    gfx_fade_in(12);

    while (1) {
        background_update();
        gfx_draw_top_bar();

        char header[80];
        snprintf(header, sizeof(header), "Saves on %s", mc);
        gfx_draw_text(header, 60, 60,
                      GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0), 5, 3);

        const char *display_texts[MAX_SAVES];
        for (int i = 0; i < save_entry_count; i++) {
            if (save_entries[i].has_icon_sys && save_entries[i].game_title[0]) {
                display_texts[i] = save_entries[i].game_title;
            } else {
                display_texts[i] = save_entries[i].folder_name;
            }
        }

        menu_draw(display_texts, save_entry_count, 90, 140);

        // Optional: show subtitle / fallback text under selected item
        int sel = menu_get_current_item();
		if (save_entry_count > 0) {
			int sel = menu_get_current_item();
			if (sel >= 0 && sel < save_entry_count) {
				SaveEntry *e = &save_entries[sel];

				int scroll = menu_get_offset();
				int visible_line = sel - scroll;

				// Only draw if this item is actually visible on screen
				if (visible_line >= 0 && visible_line < menu_max_lines) {
					int base_y = 140;                           // same as menu_draw() start Y
					int line_height = menu_line_height;         // use the actual value from menu_init
					int y = base_y + visible_line * line_height + 24;  // 24 = space below main text

					u64 subtitle_color = GS_SETREG_RGBAQ(0xCC, 0xCC, 0xFF, 0x70, 0);
					u64 fallback_color  = GS_SETREG_RGBAQ(0x88, 0x88, 0x88, 0x60, 0);

					if (e->has_icon_sys && e->game_subtitle[0] != '\0') {
						gfx_draw_text(e->game_subtitle, 120, y, subtitle_color, 3, 2);
					} else if (!e->has_icon_sys) {
						gfx_draw_text("(no icon.sys)", 120, y, fallback_color, 3, 2);
					}

					// Optional: always show folder name in very small text
					if (e->has_icon_sys) {
						int folder_y = y + 16;
						gfx_draw_text(e->folder_name, 120, folder_y,
									  GS_SETREG_RGBAQ(0xAA,0xAA,0xAA,0x50,0), 2, 1);
					}
				}
			}
		}

        gfx_flip();
        gfx_exec();

        u32 pressed = pad_get_pressed(0);

        if (pressed & PAD_DOWN)  menu_increment();
        if (pressed & PAD_UP)    menu_decrement();

        if (pressed & (PAD_TRIANGLE | PAD_CIRCLE)) {
            gfx_fade_out(12);
            return;
        }

        // Future: if (pressed & PAD_CROSS) → open folder, list files, etc.
    }
}

// ──────────────────────────────────────────────
// Main entry point
// ──────────────────────────────────────────────

int savemanager_show(void) {
    while (1) {
        int mc = select_memory_card_screen();
        if (mc < 0) {
            return 0;           // exit save manager
        }

        show_save_browser(mc);
    }

    return 0;
}
