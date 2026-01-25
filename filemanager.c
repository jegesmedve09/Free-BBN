#include <tamtypes.h>
#include <kernel.h>
#include <stdio.h>
#include <dirent.h>     // ← newlib: opendir, readdir, closedir
#include <sys/stat.h>   // ← for stat() to check if dir/file
#include <string.h>
#include <stdlib.h>

#include "gfx.h"
#include "background.h"
#include "utils.h"
#include "pad.h"
#include "menu.h"

// Use static buffers — avoid tiny char*
#define MAX_PATH 511
static char current_path[MAX_PATH + 1] = "";           // current folder
static char selected_file[MAX_PATH + 1] = "";          // what we return

// We'll collect directory entries here (very simple version — fixed max)
#define MAX_ENTRIES 128
static char *dir_list[MAX_ENTRIES];                    // pointers to names
static int dir_count = 0;
static int is_dir_list_valid = 0;                      // flag to reload when path changes

// Helper: reload directory contents into dir_list[]
static void refresh_directory(const char *path, const char **extensions) {
    int i;
    // Free old strings if any
    for (i = 0; i < dir_count; i++) {
        if (dir_list[i]) free(dir_list[i]);
        dir_list[i] = NULL;
    }
    dir_count = 0;

    DIR *d = opendir(path);
    if (!d) return;  // failed to open → keep empty list

    struct dirent *ent;
    while ((ent = readdir(d)) != NULL) {
        if (dir_count >= MAX_ENTRIES - 1) break;  // safety

        const char *name = ent->d_name;

        // Skip . and ..
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) continue;

        // Build full path for stat
        char full[MAX_PATH + 1];
        snprintf(full, sizeof(full), "%s%s", path, name);

        struct stat st;
        if (stat(full, &st) != 0) continue;  // skip broken entries

        int is_folder = S_ISDIR(st.st_mode);

        // Show folders always
        if (is_folder) {
            dir_list[dir_count] = strdup(name);  // copy name
            if (dir_list[dir_count]) dir_count++;
            continue;
        }

        // For files: check extensions if provided
        if (extensions) {
            int match = 0;
            const char **ext = extensions;
            while (*ext) {
                size_t len = strlen(*ext);
                size_t namelen = strlen(name);
                if (namelen >= len && strcasecmp(name + namelen - len, *ext) == 0) {
                    match = 1;
                    break;
                }
                ext++;
            }
            if (!match) continue;
        }

        // File allowed → add
        dir_list[dir_count] = strdup(name);
        if (dir_list[dir_count]) dir_count++;
    }

    closedir(d);
    is_dir_list_valid = 1;
}

char *filemanager_show(const char **file_extensions)
{
    selected_file[0] = '\0';   // reset return value

    while (1)
    {
        background_update();
        gfx_draw_top_bar();

        // Show current path (or hint if at root)
        const char *display_path = current_path[0] ? current_path : "[Select device]";
        gfx_draw_text(display_path, 40, 40, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0), 5, 4);

        // ──────────────────────────────────────
        // Decide menu content
        // ──────────────────────────────────────
        int at_device_select = (current_path[0] == '\0');

        if (at_device_select)
        {
            // Static device list
            menu_draw(menu_items, 20, 60, 60, 20,
                      GS_SETREG_RGBAQ(255,255,0,128,0),
                      GS_SETREG_RGBAQ(0x60,0x60,0x60,0x80,0),
                      4, 8, 5);
        }
        else
        {
            // Folder contents
            if (!is_dir_list_valid) {
                refresh_directory(current_path, file_extensions);
            }

            if (dir_count > 0) {
                // menu_draw expects const char ** — we have char *[]
                menu_draw((const char **)dir_list, dir_count,
                          20, 60, 60, 20,
                          GS_SETREG_RGBAQ(255,255,0,128,0),
                          GS_SETREG_RGBAQ(0x60,0x60,0x60,0x80,0),
                          4, 8, 5);
            } else {
                // Empty folder
                gfx_draw_text("Empty folder", 40, 100,
                              GS_SETREG_RGBAQ(0xFF,0x80,0x80,0x80,0), 5, 4);
            }
        }

        gfx_draw_text("\xFF\x00/\xFF\x01 Navigate   \xFF\x06 X Enter/Select file   \xFF\x09 O Back/Up", 
                      5, 480, GS_SETREG_RGBAQ(0x70,0x70,0x70,0x80,0), 5, 4);

        gfx_flip();
        gfx_exec();

        u32 buttons = pad_get_buttons(0);

        if (buttons & PAD_UP) {
            menu_increment();
            FuckAroundSilentlyMs(200);
        }
        if (buttons & PAD_DOWN) {
            menu_decrement();
            FuckAroundSilentlyMs(200);
        }

        if (buttons & PAD_CROSS)
        {
            FuckAroundSilentlyMs(200);

            int idx = menu_get_current_item();

            if (at_device_select)
            {
                // Enter selected device root
                strncpy(current_path, menu_items[idx], MAX_PATH);
                current_path[MAX_PATH] = '\0';
                if (current_path[strlen(current_path)-1] != '/') {
                    strncat(current_path, "/", MAX_PATH - strlen(current_path));
                }
                is_dir_list_valid = 0;  // force reload
                menu_reset_current_item();  // reset cursor
            }
            else
            {
                // Folder contents mode
                if (idx >= dir_count) continue;

                const char *name = dir_list[idx];
                char full[MAX_PATH + 1];
                snprintf(full, sizeof(full), "%s%s", current_path, name);

                struct stat st;
                if (stat(full, &st) != 0) continue;

                if (S_ISDIR(st.st_mode))
                {
                    // Enter folder
                    strncat(current_path, name, MAX_PATH - strlen(current_path));
                    if (current_path[strlen(current_path)-1] != '/') {
                        strncat(current_path, "/", MAX_PATH - strlen(current_path));
                    }
                    is_dir_list_valid = 0;  // reload
                    menu_reset_current_item();
                }
                else
                {
                    // It's a file → this is our selection!
                    strncpy(selected_file, full, MAX_PATH);
                    selected_file[MAX_PATH] = '\0';

                    // Optional: add trailing null safety or log
                    return selected_file;   // ← exit function with selected path
                }
            }
        }

        if (buttons & PAD_CIRCLE)
        {
            FuckAroundSilentlyMs(200);

            if (current_path[0] == '\0') {
                return NULL;   // cancel / exit at top level
            }

            // Go up one folder
            char *last_slash = strrchr(current_path, '/');
            if (last_slash) {
                // If ends with / and is device root like "mc0:/" → back to device select
                if (last_slash == current_path + strlen(current_path) - 1 &&
                    strlen(current_path) <= 7) {  // rough check for "xx0:/"
                    current_path[0] = '\0';
                } else {
                    // Cut to parent (keep trailing /)
                    *(last_slash + 1) = '\0';
                }
            } else {
                current_path[0] = '\0';
            }

            is_dir_list_valid = 0;  // force reload on next frame
            menu_reset_current_item();
        }
    }
}
