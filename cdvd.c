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

int disc_inserted(){
	int type;
	type = CdGetDiskType();
    if (type == CDVD_TYPE_NODISK){return 0;}else{return 1;}
	
}

int disc_ready(){
	if (cdDiskReady(0)){return 1;}else{return 0;}
	
}

void disc_launch_ps2_game(void)
{
    char cnf[MAX_CNF_SIZE];
    char boot_path[256];
    int fd;

    SifInitRpc(0);
    cdInit(CDVD_INIT_INIT);


    //wait_for_disc();

    fd = open(SYSTEM_CNF_PATH, O_RDONLY);
    if (fd < 0)
        return;

    memset(cnf, 0, sizeof(cnf));
    read(fd, cnf, sizeof(cnf) - 1);
    close(fd);

    char *p = strstr(cnf, "BOOT2");
    if (!p){return;}
    p = strchr(p, '=');
    if (!p){return;}
    p++; // skip '='
    while (*p == ' '){p++;}
    
    strcpy(boot_path, p);
    
    // Trim newline
    char *e = strchr(boot_path, '\r');
    if (e) *e = 0;
    e = strchr(boot_path, '\n');
    if (e) *e = 0;

    // BOOT2 usually looks like: cdrom0:\SLUS_203.12;1
    FlushCache(0);
    FlushCache(2);

    LoadExecPS2(boot_path, 0, NULL);
}

