#ifndef SETTINGS_H
#define SETTINGS_H

int settings_init(void);
char **settings_read_config(const char *filename);
char *settings_save_config(const char *filename, const char *data);

#endif
