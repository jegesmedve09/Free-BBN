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
	//int fd = ope("mass:/FREEBBN/system")
	//if (fd < 0) {}
	
	if (DEV_EXIST("mass:/FREEBBN/")){ savepath = "mass:/FREEBBN/"; }
	else if (DEV_EXIST("mass0:/FREEBBN/")){ savepath = "mass0:/FREEBBN/"; }
	else if (DEV_EXIST("mass1:/FREEBBN/")){ savepath = "mass1:/FREEBBN/"; }
	else if (DEV_EXIST("mass2:/FREEBBN/")){ savepath = "mass2:/FREEBBN/"; }
	else if (DEV_EXIST("mass3:/FREEBBN/")){ savepath = "mass3:/FREEBBN/"; }
	else if (DEV_EXIST("mass4:/FREEBBN/")){ savepath = "mass4:/FREEBBN/"; }
	else if (DEV_EXIST("mass5:/FREEBBN/")){ savepath = "mass5:/FREEBBN/"; }
	else if (DEV_EXIST("mass6:/FREEBBN/")){ savepath = "mass6:/FREEBBN/"; }
	else if (DEV_EXIST("mass7:/FREEBBN/")){ savepath = "mass7:/FREEBBN/"; }
	else if (DEV_EXIST("mc0:/FREEBBN/")){ savepath = "mc0:/FREEBBN/"; }
	else if (DEV_EXIST("mc1:/FREEBBN/")){ savepath = "mc1:/FREEBBN/"; }
	else if (DEV_EXIST("mc2:/FREEBBN/")){ savepath = "mc2:/FREEBBN/"; }
	else if (DEV_EXIST("mc3:/FREEBBN/")){ savepath = "mc3:/FREEBBN/"; }
	else if (DEV_EXIST("mc4:/FREEBBN/")){ savepath = "mc4:/FREEBBN/"; }
	else if (DEV_EXIST("mc5:/FREEBBN/")){ savepath = "mc5:/FREEBBN/"; }
	else if (DEV_EXIST("mc6:/FREEBBN/")){ savepath = "mc6:/FREEBBN/"; }
	else if (DEV_EXIST("mc7:/FREEBBN/")){ savepath = "mc7:/FREEBBN/"; }
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


char *settings_read_file(const char *path, char **out_buffer)
{
    if (!path || !*path || !out_buffer)
        return NULL;

    int fd = open(path, O_RDONLY);
    if (fd < 0)
        return NULL;

    struct stat st;
    if (fstat(fd, &st) < 0 || st.st_size <= 0) {
        close(fd);
        return NULL;
    }

    size_t size = st.st_size;

    void *buf = malloc(size + 1);
    if (!buf) {
        close(fd);
        return NULL;
    }

    ssize_t rd = read(fd, buf, size);
    close(fd);

    if (rd != (ssize_t)size) {
        free(buf);
        return NULL;
    }

    ((char *)buf)[size] = 0; // safe NUL terminator

    *out_buffer = buf;
    return buf;
}
