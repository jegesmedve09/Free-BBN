#include <tamtypes.h>
#include <kernel.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "utils.h"

char *savepath = "";

int settings_init(void)
{
	//int fd = ope("mass:/CONFIG/system")
	//if (fd < 0) {}
	
	if (DEV_EXIST("mass:/CONFIG/")){ savepath = "mass:/"; }
	else if (DEV_EXIST("mass0:/CONFIG/")){ savepath = "mass0:/"; }
	else if (DEV_EXIST("mass1:/CONFIG/")){ savepath = "mass1:/"; }
	else if (DEV_EXIST("mass2:/CONFIG/")){ savepath = "mass2:/"; }
	else if (DEV_EXIST("mass3:/CONFIG/")){ savepath = "mass3:/"; }
	else if (DEV_EXIST("mass4:/CONFIG/")){ savepath = "mass4:/"; }
	else if (DEV_EXIST("mass5:/CONFIG/")){ savepath = "mass5:/"; }
	else if (DEV_EXIST("mass6:/CONFIG/")){ savepath = "mass6:/"; }
	else if (DEV_EXIST("mass7:/CONFIG/")){ savepath = "mass7:/"; }
	else if (DEV_EXIST("mc0:/CONFIG/")){ savepath = "mc0:/"; }
	else if (DEV_EXIST("mc1:/CONFIG/")){ savepath = "mc1:/"; }
	else if (DEV_EXIST("mc2:/CONFIG/")){ savepath = "mc2:/"; }
	else if (DEV_EXIST("mc3:/CONFIG/")){ savepath = "mc3:/"; }
	else if (DEV_EXIST("mc4:/CONFIG/")){ savepath = "mc4:/"; }
	else if (DEV_EXIST("mc5:/CONFIG/")){ savepath = "mc5:/"; }
	else if (DEV_EXIST("mc6:/CONFIG/")){ savepath = "mc6:/"; }
	else if (DEV_EXIST("mc7:/CONFIG/")){ savepath = "mc7:/"; }
	else {savepath = "";}
	return 0;
}

int settings_save_config(const char *filename,const char *data)
{	
	if (!savepath || savepath[0] == '\0') return 0;
	
	char path[128];
	snprintf(path, sizeof(path), "%sCONFIG/%s", savepath, filename);
	
	int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) {return 0;}
	if ( ( write(fd, data, strlen(data)) ) != strlen(data) ) {close(fd); return 0;}
	close(fd);
	return 1;
}

char **settings_read_config(const char *fn, char **out_buffer)
{
    if (!fn || !*fn || !savepath || !*savepath) return NULL;

    char p[128];
    snprintf(p, sizeof(p), "%sCONFIG/%s", savepath, fn);

    int fd = open(p, O_RDONLY);
    if (fd < 0) return NULL;

    struct stat st;
    if (fstat(fd, &st) < 0 || st.st_size <= 0) { close(fd); return NULL; }

    size_t sz = st.st_size;
    char *buf = malloc(sz + 1);
    if (!buf) { close(fd); return NULL; }

    if (read(fd, buf, sz) != (int)sz) { close(fd); free(buf); return NULL; }
    close(fd);
    buf[sz] = '\0';

    int n = 0;
    for (char *q = buf; *q; q++) if (*q == '\n') n++;
    if (buf[sz-1] != '\n') n++;
    n = n ? n : 1;

    char **lines = malloc((n + 1) * sizeof(char*));
    if (!lines) { free(buf); return NULL; }

    int i = 0;
    char *t = strtok(buf, "\n\r");
    while (t && i < n) {
        lines[i++] = t;
        t = strtok(NULL, "\n\r");
    }
    lines[i] = NULL;

	*out_buffer = buf;
    return lines;
}
