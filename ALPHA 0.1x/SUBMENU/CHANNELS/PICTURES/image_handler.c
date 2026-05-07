
#include <tamtypes.h>
#include <kernel.h>
#include <string.h>

#include <stdlib.h>

#include "../../../settings.h"

char *fd;

static char *pXm_skip(char *p)
{
    while (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')
        p++;

    if (*p == '#') {
        while (*p && *p != '\n') p++;
        return pXm_skip(p);
    }

    return p;
}

void image_load(char *filepath, char *rgb, int *w, int *h) {
    char *buffer = NULL;
    char *fd = settings_read_file(filepath, &buffer);
    if (!fd) return;

    if (fd[0] == 'P' && fd[1] == '6') {
        fd += 2;
        fd = pXm_skip(fd);
        *w = atoi(fd);
        //if (*w <=0) { free(buffer); return; }
        
        while (*fd > ' ') fd++;
        fd = pXm_skip(fd);
        *h = atoi(fd);
        //if (*h <=0){ free(buffer); return; }
        
        while (*fd > ' ') fd++;
        fd = pXm_skip(fd);
        int max = atoi(fd);
        //if (max != 255) { free(buffer); return; }
        
        while (*fd > ' ') fd++;
        fd = pXm_skip(fd);  // Skip to data

        if (max != 255 || *w <= 0 || *h <= 0) {
            free(buffer);
            return;
        }

        // Copy pixel data
        //if (rgb)
        //{
		//	if ( (*w) * (*h) *3 > 1024*1024*2 ) { free(buffer); return; }
			memcpy(rgb, fd, (*w) * (*h) * 3);
		//}
    }
    free(buffer);
}
