#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

/* ---------------- DEVICES ---------------- */

static const char *devices[] = {
    "mc0:/",
    "mc1:/",
    "mc2:/",
    "mc3:/",
    "mc4:/",
    "mc5:/",
    "mc6:/",
    "mc7:/",
    "mass:/",
    "mass0:/",
    "mass1:/",
    "mass2:/",
    "mass3:/",
    "mass4:/",
    "mass5:/",
    "mass6:/",
    "mass7:/",
    "cdvd:/",
    "host:/",
};

/* ---------------- STATE ---------------- */

static FileEntry entries[MAX_ENTRIES];
static char item_strings[MAX_ENTRIES][128];
static const char *menu_items[MAX_ENTRIES];

static int entry_count = 19;

static char cwd[1024];
static char root[32];

static int mode = 0; /* 0 = device select, 1 = browser */

/* ---------------- UTILS ---------------- */

static int ext_match(const char *name, const char **exts)
{
    if (!exts) return 1;

    const char *dot = strrchr(name, '.');
    if (!dot) return 0;
    dot++;

    for (int i = 0; exts[i]; i++) {
        if (!strcasecmp(dot, exts[i]))
            return 1;
    }
    return 0;
}

/* ---------------- MENU BUILDERS ---------------- */

static void build_device_menu(void)
{
    entry_count = 0;
    memset(entries, 0, sizeof(entries));
    memset(menu_items, 0, sizeof(menu_items));

    for (int i = 0; devices[i] && entry_count < MAX_ENTRIES; i++) {
        DIR *d = opendir(devices[i]);
        if (!d) continue;
        closedir(d);

        snprintf(item_strings[entry_count], sizeof(item_strings[0]),
                 "%s", devices[i]);

        menu_items[entry_count] = item_strings[entry_count];
        entry_count++;
    }

    menu_reset_current_item();
}

static void build_dir_menu(void)
{
    entry_count = 0;
    memset(entries, 0, sizeof(entries));
    memset(menu_items, 0, sizeof(menu_items));

    DIR *d = opendir(cwd);
    if (!d) return;

    /* add .. unless at root */
    if (strcmp(cwd, root) != 0) {
        strcpy(entries[0].name, "..");
        entries[0].is_dir = 1;

        strcpy(item_strings[0], "[DIR] ..");
        menu_items[0] = item_strings[0];

        entry_count = 1;
    }

    struct dirent *ent;
    while ((ent = readdir(d)) && entry_count < MAX_ENTRIES) {
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
            continue;

        FileEntry *e = &entries[entry_count];
        strcpy(e->name, ent->d_name);

        char full[1024];
        snprintf(full, sizeof(full), "%s%s", cwd, ent->d_name);

        struct stat st;
        e->is_dir = (stat(full, &st) == 0 && S_ISDIR(st.st_mode));

        if (e->is_dir)
            snprintf(item_strings[entry_count], sizeof(item_strings[0]),
                     "[DIR]  %s", e->name);
        else
            snprintf(item_strings[entry_count], sizeof(item_strings[0]),
                     "[FILE] %s", e->name);

        menu_items[entry_count] = item_strings[entry_count];
        entry_count++;
    }

    closedir(d);
    menu_reset_current_item();
}

/* ---------------- MAIN ENTRY ---------------- */

char *filemanager_show(const char **extensions)
{
    char *result = NULL;

    mode = 0;
    build_device_menu();

    gfx_fade_in(10);

    while (!result) {
        u32 pressed = pad_get_buttons(0);

        background_update();
        gfx_draw_top_bar();

        if (mode == 0) {
			gfx_draw_text("Select Device", 40, 60, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 10, 4);
			gfx_draw_text("\xFF\x00/\xFF\x01 Navigate \xFF\x06 Select \xFF\x09 Back",5, 480,GS_SETREG_RGBAQ(0x70, 0x70, 0x70, 0x80, 0x00),5, 4);
            menu_draw(menu_items, entry_count, 40, 120);
            
            if (pressed & PAD_UP){
				menu_decrement();
				FuckAroundSilentlyMs(300);
            }
            
            if (pressed & PAD_DOWN){
				menu_increment();
				FuckAroundSilentlyMs(300);
			}

            if (pressed & PAD_CROSS && entry_count > 0) {
                int sel = menu_get_current_item();
                strcpy(root, menu_items[sel]);
                strcpy(cwd, root);
                mode = 1;
                build_dir_menu();
				FuckAroundSilentlyMs(300);
            }

            if (pressed & PAD_TRIANGLE)
                break;
        }
        else {
            gfx_draw_text(cwd, 40, 60,
                GS_SETREG_RGBAQ(255,255,255,0x80,0), 10, 4);

            menu_draw(menu_items, entry_count, 40, 120);

            if (pressed & PAD_UP){
				menu_decrement();
				FuckAroundSilentlyMs(300);
            }
            
            if (pressed & PAD_DOWN){
				menu_increment();
				FuckAroundSilentlyMs(300);
			}
			
            if (pressed & PAD_CROSS && entry_count > 0) {
                int sel = menu_get_current_item();
                FileEntry *e = &entries[sel];

                if (e->is_dir) {
                    if (!strcmp(e->name, "..")) {
                        size_t len = strlen(cwd);

						/* remove trailing slash */
						if (len > 0 && cwd[len - 1] == '/')
							cwd[len - 1] = 0;

						char *p = strrchr(cwd, '/');

						if (p && strlen(cwd) > strlen(root))
							p[1] = 0;
						else
							strcpy(cwd, root);
                    } else {
                        strcat(cwd, e->name);
                        strcat(cwd, "/");
                    }
                    build_dir_menu();
                }else {
					if (ext_match(e->name, extensions)) {
						// Make sure cwd ends with '/'
						char full[1024];
						snprintf(full, sizeof(full), "%s%s", cwd, e->name);
						result = strdup(full);
						printf("Selected file: %s\n", result); // optional debug
					}else{
						background_update();
						gfx_draw_top_bar();
						gfx_draw_text("Unsupported extension", 40, 60,
						GS_SETREG_RGBAQ(255,255,255,0x80,0), 10, 4);
						gfx_flip();
						gfx_exec();
						FuckAroundSilentlyMs(2000);
					}
				}

				FuckAroundSilentlyMs(300);
            }

            if (pressed & PAD_TRIANGLE) {
                if (!strcmp(cwd, root)) {
                    mode = 0;
                    build_device_menu();
                } else {
					size_t len = strlen(cwd);

					/* remove trailing slash */
					if (len > 0 && cwd[len - 1] == '/')
						cwd[len - 1] = 0;

					char *p = strrchr(cwd, '/');

					if (p && strlen(cwd) > strlen(root))
						p[1] = 0;
					else
						strcpy(cwd, root);
                    build_dir_menu();
                }
				FuckAroundSilentlyMs(300);
            }
        }

        gfx_flip();
        gfx_exec();
    }

    gfx_fade_out(10);
    menu_reset_current_item();

    return result ? result : "";
}
