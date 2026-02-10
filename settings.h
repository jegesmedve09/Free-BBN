#ifndef SETTINGS_H
#define SETTINGS_H

int settings_init(void);
char **settings_read_config(const char *filename, char **out_buffer);
int settings_save_config(const char *filename, const char *data);
char *settings_read_file(const char *path, char **out_buffer);
#endif
