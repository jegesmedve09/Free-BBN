#include <kernel.h>
#include <sifrpc.h>
#include <libcdvd.h>
#include <loadfile.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define SYSTEM_CNF_PATH "cdrom0:\\SYSTEM.CNF;1"
#define MAX_CNF_SIZE   2048

int cdvd_tray_open(void)
{
    int ret, status;

    ret = sceCdTrayReq(SCECdTrayOpen, &status);
    if (ret <= 0) return -1;  // failed to send request

    // Poll until command finishes
    while (1) {
        ret = sceCdTrayReq(SCECdTrayCheck, &status);
        if (ret <= 0) return -2;

        if (status == 0) break;   // done (tray fully open)
        // status may be: 1=opening, 2=closing, etc. — check libcdvd docs for exact values

        // Optional: SleepThread() or small delay to avoid busy-loop CPU hog
    }

    return 0;  // success
}

int cdvd_tray_close(void)
{
    int ret, status;

    ret = sceCdTrayReq(SCECdTrayClose, &status);
    if (ret <= 0) return -1;

    while (1) {
        ret = sceCdTrayReq(SCECdTrayCheck, &status);
        if (ret <= 0) return -2;
        if (status == 0) break;
    }

    return 0;
}

int cdvd_tray_is_open(void)
{
    int status;
    if (sceCdTrayReq(SCECdTrayCheck, &status) > 0) {
        return (status != 0);  // non-zero usually means open/in-motion
    }
    return -1;  // error
}

int cdvd_tray_toggle(void)
{
	if (cdvd_tray_is_open())
	{
		cdvd_tray_close();
	}
	else
	{
		cdvd_tray_open();
	}
}

int cdvd_disc_inserted(void)
{
	int type;
	type = CdGetDiskType();
    if (type == CDVD_TYPE_NODISK)
    {
		return 0;
	}
	else
	{
		return 1;
	}
}

int cdvd_disc_ready(void){
	if (cdDiskReady(0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void cdvd_launch_ps2_game(void)
{
    char cnf[MAX_CNF_SIZE];
    char boot_path[256];
    int fd;

    SifInitRpc(0);
    cdInit(CDVD_INIT_INIT);

    fd = open(SYSTEM_CNF_PATH, O_RDONLY);
    
    if (fd < 0)
    {
        return;
	}
	
    memset(cnf, 0, sizeof(cnf));
    read(fd, cnf, sizeof(cnf) - 1);
    close(fd);

    char *p = strstr(cnf, "BOOT2");
    
    if (!p)
    {
		return;
	}
	
    p = strchr(p, '=');
    
    if (!p)
    {
		return;
	}
	
    p++; // skip '='
    
    while (*p == ' ')
    {
		p++;
	}
    
    strcpy(boot_path, p);
    
    // Trim newline
    char *e = strchr(boot_path, '\r');
    
    if (e)
    {
		*e = 0;
	}
    
    e = strchr(boot_path, '\n');
    
    if (e)
    {
		*e = 0;
	}

    // BOOT2 usually looks like: cdrom0:\SLUS_203.12;1
    FlushCache(0);
    FlushCache(2);

    LoadExecPS2(boot_path, 0, NULL);
}

