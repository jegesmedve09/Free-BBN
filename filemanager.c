#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "gfx.h"
#include "pad.h"
#include "cdvd.h"
#include "background.h"
#include "menu.h"
#include "utils.h"
#include "textinput.h"
#include <errno.h>

#define MAX_ENTRIES 256

typedef struct {
    char name[128];
    bool is_dir;
    u64 size;
} FileEntry;

/* Devices list */
static const char *devices[] = {
    "mc0:/", "mc1:/", "mc2:/", "mc3:/", "mc4:/", "mc5:/", "mc6:/", "mc7:/",
    "mass:/", "mass0:/", "mass1:/", "mass2:/", "mass3:/", "mass4:/", "mass5:/", "mass6:/", "mass7:/",
    "cdvd:/", "host:/",
    NULL
};

/* State */
static FileEntry entries[MAX_ENTRIES];
static char item_strings[MAX_ENTRIES][128];
static const char *menu_items[MAX_ENTRIES];
static char copy_string[2048] = {0};
static char copy_name[128] = {0};

static int entry_count = 0;
static char cwd[1024];
static char root[32];
static int mode = 0; /* 0 = device select, 1 = browser */
static int is_usb = 0;

/* Utils */
static int ext_match(const char *name, const char **exts) {
    if (!exts || !exts[0] || exts[0][0] == '\0') return 1; /* Allow all if NULL, empty array, or first is empty string */
    const char *dot = strrchr(name, '.');
    if (!dot) return 0;
    dot++;
    for (int i = 0; exts[i]; i++) {
        if (!strcasecmp(dot, exts[i])) return 1;
    }
    return 0;
}

/* Menu builders */
static void build_device_menu(void) {
    entry_count = 0;
    memset(entries, 0, sizeof(entries));
    memset(item_strings, 0, sizeof(item_strings));
    memset(menu_items, 0, sizeof(menu_items));
    for (int i = 0; devices[i]; i++) {
        DIR *d = opendir(devices[i]);
        if (!d) continue;
        closedir(d);
        snprintf(item_strings[entry_count], sizeof(item_strings[0]), "%s", devices[i]);
        menu_items[entry_count] = item_strings[entry_count];
        entries[entry_count].is_dir = 1; /* Devices treated as dirs */
        strcpy(entries[entry_count].name, devices[i]);
        entry_count++;
        if (entry_count >= MAX_ENTRIES) break;
    }
    menu_reset_current_item();
}

static void build_dir_menu(void) {
    entry_count = 0;
    memset(entries, 0, sizeof(entries));
    memset(item_strings, 0, sizeof(item_strings));
    memset(menu_items, 0, sizeof(menu_items));
    DIR *d = NULL;
    int retries = 0;
    const int max_retries = 8; /* ~12 sec total */
    while (!d && retries < max_retries) {
        d = opendir(cwd);
        if (!d) FuckAroundSilentlyMs(1500); /* Settle time for USB */
        retries++;
    }
    if (!d) {
        /* Handle failure gracefully */
        menu_reset_current_item();
        return;
    }
    /* Add .. unless at root */
    if (strcmp(cwd, root) != 0) {
        strcpy(entries[0].name, "..");
        entries[0].is_dir = 1;
        strcpy(item_strings[0], "\xFF\x22 ..");
        menu_items[0] = item_strings[0];
        entry_count = 1;
    }
    struct dirent *ent;
    while ((ent = readdir(d)) != NULL) {
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")) continue;
        if (entry_count >= MAX_ENTRIES) break;
        FileEntry *e = &entries[entry_count];
        strcpy(e->name, ent->d_name);
        char full[1024];
        snprintf(full, sizeof(full), "%s%s", cwd, ent->d_name);
        struct stat st;
        e->is_dir = (stat(full, &st) == 0 && S_ISDIR(st.st_mode));
        e->size = st.st_size;
        if (e->is_dir)
        {
            snprintf(item_strings[entry_count], sizeof(item_strings[0]), "\xFF\x22 %s", e->name);
        }
        else
        {
            char size[16];
            if      (e->size >= 1024LL * 1024 * 1024) { snprintf(size, sizeof(size), "%.2f GB", (double)e->size / (1024.0 * 1024 * 1024)); }
            else if (e->size >= 1024LL * 1024)        { snprintf(size, sizeof(size), "%.2f MB", (double)e->size / (1024.0 * 1024)); }
            else if (e->size >= 1024LL)               { snprintf(size, sizeof(size), "%.2f kB", (double)e->size / (1024.0)); }
            else    { snprintf(size, sizeof(size), "%d B", e->size); }
            snprintf(item_strings[entry_count], sizeof(item_strings[0]), "\xFF\x23 %s   %s", size, e->name);
        }   
        menu_items[entry_count] = item_strings[entry_count];
        entry_count++;
        FuckAroundSilentlyMs(10); /* Avoid IOP flood */
    }
    closedir(d);
    menu_reset_current_item();
}


int copy_file(const char *src, const char *dst)
{
    FILE *in = fopen(src, "rb");
    if (!in) return -1;

    FILE *out = fopen(dst, "wb");
    if (!out) {
        fclose(in);
        return -1;
    }

    char *buffer = malloc(32 * 1024);  // 32KB buffer - good balance for PS2
    if (!buffer) {
        fclose(in);
        fclose(out);
        return -1;
    }

    size_t bytes;
    while ((bytes = fread(buffer, 1, 32*1024, in)) > 0) {
        if (fwrite(buffer, 1, bytes, out) != bytes) {
            free(buffer);
            fclose(in);
            fclose(out);
            return -1;
        }
        // Small yield so IOP doesn't completely freeze
        FuckAroundSilentlyMs(1);
    }

    free(buffer);
    fclose(in);
    fclose(out);
    return 0;
}



/* Main function */
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
        if (entry_count == 0 && mode == 1) {
            const char *msg = is_usb ? "USB dir failed - replug? Empty?" : "Empty Device";
            gfx_draw_text(msg, 40, 100, GS_SETREG_RGBAQ(0xFF,0x00,0x00,0x80,0), 10, 4);
        }
        if (mode == 0) {
            gfx_draw_text("Select Device", 40, 60, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 10, 4);
            menu_draw(menu_items, entry_count, 40, 120);
            if (pressed & PAD_UP) {
                menu_decrement();
                FuckAroundSilentlyMs(300);
            }
            if (pressed & PAD_DOWN) {
                menu_increment();
                FuckAroundSilentlyMs(300);
            }
            if (pressed & PAD_CROSS && entry_count > 0) {
                int sel = menu_get_current_item();
                strcpy(root, entries[sel].name);
                strcpy(cwd, root);
                is_usb = (strstr(root, "mass") != NULL);
                mode = 1;
                build_dir_menu();
                FuckAroundSilentlyMs(300);
            }
            if (pressed & PAD_TRIANGLE) break; /* Exit */
        } else {
            gfx_draw_text(cwd, 40, 60, GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00), 10, 4);
            menu_draw(menu_items, entry_count, 40, 120);
            if (pressed & PAD_UP) {
                menu_decrement();
                FuckAroundSilentlyMs(300);
            }
            if (pressed & PAD_DOWN) {
                menu_increment();
                FuckAroundSilentlyMs(300);
            }
            if (pressed & PAD_CROSS && entry_count > 0) {
                int sel = menu_get_current_item();
                FileEntry *e = &entries[sel];
                if (e->is_dir) {
                    if (!strcmp(e->name, "..")) {
                        size_t len = strlen(cwd);
                        if (len > 0 && cwd[len - 1] == '/') cwd[len - 1] = '\0';
                        char *p = strrchr(cwd, '/');
                        if (p && strlen(cwd) > strlen(root)) p[1] = '\0';
                        else strcpy(cwd, root);
                    } else {
                        strcat(cwd, e->name);
                        strcat(cwd, "/");
                    }
                    build_dir_menu();
                }
                else if (manager_mode)
                {
					static const char *elf_extensions[] = {"elf","ELF","Elf","eLf","elF","ELf","eLF","ElF", NULL};
					if (ext_match(e->name, elf_extensions))
					{
                        char full[1024];
                        snprintf(full, sizeof(full), "%s%s", cwd, e->name);
                        cdvd_run_elf(full);
					}
				}
                else
                {
                    if (ext_match(e->name, extensions)) {
                        char full[1024];
                        snprintf(full, sizeof(full), "%s%s", cwd, e->name);
                        result = strdup(full);
                        break;
                    } else {
						for (int i = 0; i < 100; i++){
							background_update();
							gfx_draw_top_bar();
							gfx_draw_text("Unsupported extension", 40, 60, GS_SETREG_RGBAQ(0xFF,0x00,0x00,0x80,0), 10, 4);
							gfx_flip();
							gfx_exec();
						}
                   }
                }
				FuckAroundSilentlyMs(300);
            }
            
				if (pressed & PAD_R2 && manager_mode && entry_count > 0)
				{
					int sel = menu_get_current_item();
					FileEntry *e = &entries[sel];

					char file_path[1024];
					snprintf(file_path, sizeof(file_path), "%s%s", cwd, e->name);

					// Simple "Cut" support
					static bool is_cut = false;

					gfx_fade_out(15);
					menu_reset_current_item();

					const char *file_option_items[] = {
						"Copy",
						"Cut",
						"Paste",
						"Delete",
						"Rename",
						"New Directory"
					};

					int option_count = 6;
					int option = 0;

					while (1)
					{
						u32 btn = pad_get_buttons(0);

						background_update();
						gfx_draw_top_bar();
						gfx_draw_text(file_path, 40, 60, GS_SETREG_RGBAQ(0xFF,0xFF,0x00,0x80,0), 10, 4);
						menu_draw(file_option_items, option_count, 40, 120);

						// Navigation
						if (btn & PAD_UP) {
							option = (option - 1 + option_count) % option_count;
							FuckAroundSilentlyMs(200);
						}
						if (btn & PAD_DOWN) {
							option = (option + 1) % option_count;
							FuckAroundSilentlyMs(200);
						}

						if (btn & PAD_CROSS)
						{
							if (option == 0) // Copy
							{
								strcpy(copy_string, file_path);
								strcpy(copy_name, e->name);
								is_cut = false;
								gfx_draw_text("File copied!", 40, 220, GS_SETREG_RGBAQ(0x00,0xFF,0x00,0xFF,0), 10, 4);
							}
							else if (option == 1) // Cut
							{
								strcpy(copy_string, file_path);
								strcpy(copy_name, e->name);
								is_cut = true;
								gfx_draw_text("File cut!", 40, 220, GS_SETREG_RGBAQ(0xFF,0xFF,0x00,0xFF,0), 10, 4);
							}
							else if (option == 2) // Paste
							{
								if (strlen(copy_string) > 0)
								{
									char dst[2048];
									snprintf(dst, sizeof(dst), "%s%s", cwd, copy_name);

									if (copy_file(copy_string, dst) == 0)
									{
										gfx_draw_text("Paste OK!", 40, 220, GS_SETREG_RGBAQ(0x00,0xFF,0x00,0xFF,0), 10, 4);
										if (is_cut)
										{
											remove(copy_string);        // delete source
											is_cut = false;
										}
									}
									else
									{
										gfx_draw_text("Paste failed!", 40, 220, GS_SETREG_RGBAQ(0xFF,0x00,0x00,0xFF,0), 10, 4);
									}
								}
							}
							else if (option == 3) // Delete
							{
								if (e->is_dir)
									rmdir(file_path);
								else
									remove(file_path);

								gfx_draw_text("Deleted", 40, 220, GS_SETREG_RGBAQ(0xFF,0x80,0x00,0xFF,0), 10, 4);
							}
							else if (option == 4) // Rename
							{
								char newname[128] = {0};
								if (textinput_get_text(newname, sizeof(newname), "New name:"))
								{
									if (newname[0] != '\0')
									{
										char newpath[2048];
										snprintf(newpath, sizeof(newpath), "%s%s", cwd, newname);

										if (rename(file_path, newpath) == 0)
											gfx_draw_text("Renamed!", 40, 220, GS_SETREG_RGBAQ(0x00,0xFF,0x00,0xFF,0), 10, 4);
										else
											gfx_draw_text("Rename failed", 40, 220, GS_SETREG_RGBAQ(0xFF,0x00,0x00,0xFF,0), 10, 4);
									}
								}
							}
							else if (option == 5) // New Directory
							{
								char dirname[128] = {0};
								if (textinput_get_text(dirname, sizeof(dirname), "Folder name:"))
								{
									if (dirname[0] != '\0')
									{
										char newpath[2048];
										snprintf(newpath, sizeof(newpath), "%s%s", cwd, dirname);

										if (mkdir(newpath, 0777) == 0)
											gfx_draw_text("Folder created!", 40, 220, GS_SETREG_RGBAQ(0x00,0xFF,0x00,0xFF,0), 10, 4);
										else
										{
											char msg[160];
											snprintf(msg, sizeof(msg), "Failed: %s", strerror(errno));
											gfx_draw_text(msg, 40, 220, GS_SETREG_RGBAQ(0xFF,0x40,0x40,0xFF,0), 10, 4);
										}
									}
								}
							}

							FuckAroundSilentlyMs(1200);
							build_dir_menu();
							break; // exit submenu
						}

						if (btn & PAD_TRIANGLE)
						{
							break; // cancel submenu
						}

						gfx_flip();
						gfx_exec();
						FuckAroundSilentlyMs(16); // ~60fps
					}

					gfx_fade_in(15);
					FuckAroundSilentlyMs(200);
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
        gfx_draw_text("\xFF\x00/\xFF\x01 Navigate \xFF\x06 Select \xFF\x09 Back", 5, 480, GS_SETREG_RGBAQ(0x70, 0x70, 0x70, 0x80, 0x00), 5, 4);
        gfx_flip();
        gfx_exec();
    }
    gfx_fade_out(10);
    menu_reset_current_item();
    return result;
}
