#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "gfx.h"
#include "pad.h"
#include "background.h"
#include "menu.h"
#include "utils.h"

#define MAX_ENTRIES 256

typedef struct {
    char name[128];
    int is_dir;
} FileEntry;

/* Devices list – simplified to avoid multiple mass issues */
static const char *devices[] = {
    "mc0:/", "mc1:/", "mc2:/", "mc3:/", "mc4:/", "mc5:/", "mc6:/", "mc7:/",
    "mass:/", /* Only use mass:/ to avoid emulation bugs with massN: */
    "cdvd:/", "host:/",
    NULL
};

/* State */
static FileEntry entries[MAX_ENTRIES];
static char item_strings[MAX_ENTRIES][128];
static const char *menu_items[MAX_ENTRIES];
static int entry_count = 0;
static char cwd[1024];
static char root[32];
static int mode = 0; /* 0 = device select, 1 = browser */
static int is_usb = 0;

/* Utils */
static int ext_match(const char *name, const char **exts) {
    if (!exts || !exts[0] || exts[0][0] == '\0') return 1;
    const char *dot = strrchr(name, '.');
    if (!dot) return 0;
    dot++;
    for (int i = 0; exts[i]; i++) {
        if (!strcasecmp(dot, exts[i])) return 1;
    }
    return 0;
}

static void build_device_menu(void) {
    entry_count = 0;
    memset(entries, 0, sizeof(entries));
    memset(item_strings, 0, sizeof(item_strings));
    memset(menu_items, 0, sizeof(menu_items));
    for (int i = 0; devices[i]; i++) {
        printf("Checking device %s\n", devices[i]);
        DIR *d = opendir(devices[i]);
        if (!d) {
            printf("opendir failed for %s: %s (errno %d)\n", devices[i], strerror(errno), errno);
            continue;
        }
        closedir(d);
        snprintf(item_strings[entry_count], sizeof(item_strings[0]), "%s", devices[i]);
        menu_items[entry_count] = item_strings[entry_count];
        entries[entry_count].is_dir = 1;
        strcpy(entries[entry_count].name, devices[i]);
        entry_count++;
        if (entry_count >= MAX_ENTRIES) break;
        FuckAroundSilentlyMs(500); // Delay between device checks
    }
    menu_reset_current_item();
}

static void build_dir_menu(void) {
    entry_count = 0;
    memset(entries, 0, sizeof(entries));
    memset(item_strings, 0, sizeof(item_strings));
    memset(menu_items, 0, sizeof(menu_items));
    printf("build_dir_menu: Starting on %s (is_usb: %d)\n", cwd, is_usb);
    if (is_usb) FuckAroundSilentlyMs(8000); // Increased settle time for USB in emulation
    DIR *d = NULL;
    int retries = 0;
    const int max_retries = is_usb ? 30 : 3;
    const int retry_delay_ms = is_usb ? 3000 : 400;
    while (!d && retries < max_retries) {
        printf("opendir attempt %d on %s\n", retries + 1, cwd);
        d = opendir(cwd);
        if (!d) {
            printf("opendir failed: %s (errno %d)\n", strerror(errno), errno);
            FuckAroundSilentlyMs(retry_delay_ms);
            retries++;
        }
    }
    if (!d) {
        printf("Giving up on opendir after %d tries\n", max_retries);
        const char *msg = is_usb ? "USB not ready - replug or check drive in PCSX2?" : "Failed to open directory";
        gfx_draw_square(150, 130, 320, 60, GS_SETREG_RGBAQ(0, 0, 0, 0x80, 0));
        gfx_draw_text(msg, 160, 140, GS_SETREG_RGBAQ(0xFF, 0x00, 0x00, 0x80, 0), 10, 4);
        gfx_flip(); gfx_exec();
        FuckAroundSilentlyMs(3000);
        menu_reset_current_item();
        return;
    }
    printf("opendir succeeded after %d tries\n", retries);
    /* Add .. unless we're at root */
    if (strcmp(cwd, root) != 0) {
        strcpy(entries[0].name, "..");
        entries[0].is_dir = 1;
        strcpy(item_strings[0], "[DIR] ..");
        menu_items[0] = item_strings[0];
        entry_count = 1;
    }
    struct dirent *ent = NULL;
    int read_count = 0;
    const int max_reads = 1024; // Safety cap
    const int entry_delay_ms = is_usb ? 100 : 10; // Increased for emulation timing
    while (read_count < max_reads) {
        printf("readdir attempt %d...\n", read_count + 1);
        ent = readdir(d);
        if (!ent) {
            printf("readdir returned NULL (end or error: %s errno %d)\n", strerror(errno), errno);
            break;
        }
        printf("readdir got ent at %p, d_name at %p\n", (void*)ent, (void*)ent->d_name);
        if (ent->d_name[0] == '\0') {
            printf("Warning: empty d_name - skipping\n");
            continue;
        }
        read_count++;
        FuckAroundSilentlyMs(entry_delay_ms);
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")) {
            printf("Skipping . or ..\n");
            continue;
        }
        if (entry_count >= MAX_ENTRIES) {
            printf("Max entries reached\n");
            break;
        }
        printf("Processing entry %d: %s\n", entry_count, ent->d_name);
        FileEntry *e = &entries[entry_count];
        strncpy(e->name, ent->d_name, sizeof(e->name) - 1);
        e->name[sizeof(e->name) - 1] = '\0';
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s%s", cwd, e->name);
        struct stat st;
        memset(&st, 0, sizeof(st));
        printf("stat on %s...\n", fullpath);
        int stat_ret = stat(fullpath, &st);
        if (stat_ret == 0) {
            e->is_dir = S_ISDIR(st.st_mode);
            printf("stat success: is_dir=%d\n", e->is_dir);
        } else {
            printf("stat failed: %s (errno %d) - treating as file\n", strerror(errno), errno);
            e->is_dir = 0;
        }
        if (e->is_dir)
            snprintf(item_strings[entry_count], sizeof(item_strings[0]), "[DIR] %s", e->name);
        else
            snprintf(item_strings[entry_count], sizeof(item_strings[0]), "[FILE] %s", e->name);
        menu_items[entry_count] = item_strings[entry_count];
        entry_count++;
        FuckAroundSilentlyMs(entry_delay_ms);
    }
    if (read_count >= max_reads) printf("Hit read safety cap - possible loop?\n");
    closedir(d);
    printf("closedir done\n");
    if (is_usb) FuckAroundSilentlyMs(1000); // Post-close delay
    printf("build_dir_menu done: %d entries\n", entry_count);
    menu_reset_current_item();
}

/* Main filemanager function */
char *filemanager_show(const char **extensions) {
    char *result = NULL;
    int manager_mode = (extensions == NULL);
    mode = 0;
    build_device_menu();
    gfx_fade_in(10);
    while (1) {
        u32 pressed = pad_get_buttons(0);
        background_update();
        gfx_draw_top_bar();
        if (mode == 1 && entry_count == 0) {
            const char *msg = is_usb ? "USB not ready - replug or check drive?" : "Empty Directory";
            gfx_draw_text(msg, 40, 200, GS_SETREG_RGBAQ(0xFF, 0x00, 0x00, 0x80, 0), 10, 4);
        }
        if (mode == 0) {
            gfx_draw_text("Select Device", 40, 60, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0), 10, 4);
            menu_draw(menu_items, entry_count, 40, 120);
            if (pressed & PAD_UP) { menu_decrement(); FuckAroundSilentlyMs(220); }
            if (pressed & PAD_DOWN) { menu_increment(); FuckAroundSilentlyMs(220); }
            if (pressed & PAD_CROSS && entry_count > 0) {
                int sel = menu_get_current_item();
                strcpy(root, entries[sel].name);
                strcpy(cwd, root);
                size_t len = strlen(cwd);
                if (len > 0 && cwd[len - 1] != '/') strcat(cwd, "/");
                is_usb = (strstr(root, "mass") != NULL);
                if (is_usb) FuckAroundSilentlyMs(8000); // Extra long delay on USB select in emulation
                mode = 1;
                build_dir_menu();
                FuckAroundSilentlyMs(500);
            }
            if (pressed & PAD_TRIANGLE) break;
        } else {
            gfx_draw_text(cwd, 40, 60, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0), 10, 4);
            menu_draw(menu_items, entry_count, 40, 120);
            if (pressed & PAD_UP) { menu_decrement(); FuckAroundSilentlyMs(220); }
            if (pressed & PAD_DOWN) { menu_increment(); FuckAroundSilentlyMs(220); }
            if (pressed & PAD_CROSS && entry_count > 0) {
                int sel = menu_get_current_item();
                FileEntry *e = &entries[sel];
                if (e->is_dir) {
                    size_t len = strlen(cwd);
                    if (!strcmp(e->name, "..")) {
                        if (len > 0 && cwd[len - 1] == '/') cwd[len - 1] = '\0';
                        char *p = strrchr(cwd, '/');
                        if (p && strlen(cwd) > strlen(root)) p[1] = '\0';
                        else strcpy(cwd, root);
                    } else {
                        if (len > 0 && cwd[len - 1] != '/') strcat(cwd, "/");
                        strcat(cwd, e->name);
                        strcat(cwd, "/");
                    }
                    build_dir_menu();
                } else {
                    if (manager_mode) {
                        gfx_draw_square(150, 130, 320, 60, GS_SETREG_RGBAQ(0, 0, 0, 0x80, 0));
                        gfx_draw_text("File ops coming later...", 160, 140, GS_SETREG_RGBAQ(0xFF, 0xFF, 0x00, 0x80, 0), 10, 4);
                        gfx_flip(); gfx_exec();
                        FuckAroundSilentlyMs(1400);
                    } else if (ext_match(e->name, extensions)) {
                        char full[1024];
                        snprintf(full, sizeof(full), "%s%s", cwd, e->name);
                        result = strdup(full);
                        break;
                    } else {
                        gfx_draw_square(150, 130, 320, 60, GS_SETREG_RGBAQ(0, 0, 0, 0x80, 0));
                        gfx_draw_text("Wrong file type", 160, 140, GS_SETREG_RGBAQ(0xFF, 0x80, 0x00, 0x80, 0), 10, 4);
                        gfx_flip(); gfx_exec();
                        FuckAroundSilentlyMs(1600);
                    }
                }
                FuckAroundSilentlyMs(220);
            }
            if (pressed & PAD_TRIANGLE) {
                if (!strcmp(cwd, root)) {
                    mode = 0;
                    build_device_menu();
                } else {
                    size_t len = strlen(cwd);
                    if (len > 0 && cwd[len - 1] == '/') cwd[len - 1] = '\0';
                    char *p = strrchr(cwd, '/');
                    if (p && strlen(cwd) > strlen(root)) p[1] = '\0';
                    else strcpy(cwd, root);
                    build_dir_menu();
                }
                FuckAroundSilentlyMs(300);
            }
        }
        gfx_draw_text("\xFF\x00/\xFF\x01 Navigate \xFF\x06 Select \xFF\x09 Back", 5, 480,
                      GS_SETREG_RGBAQ(0x70, 0x70, 0x70, 0x80, 0), 5, 4);
        gfx_flip();
        gfx_exec();
    }
    gfx_fade_out(10);
    menu_reset_current_item();
    return result ? result : (manager_mode ? NULL : "");
}
