#ifndef CDVD_H
#define CDVD_H

int cdvd_init(void);

int cdvd_disc_inserted(void);
int cdvd_disc_ready(void);
void cdvd_launch_ps2_game(void);

int cdvd_tray_open(void);
int cdvd_tray_close(void);
int cdvd_tray_is_open(void);
int cdvd_tray_toggle(void);

void cdvd_run_elf(const char *filename);
#endif

