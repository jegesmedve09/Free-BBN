
#include <tamtypes.h>
#include <kernel.h>

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

void image_load(char *filepath, char **out_buffer, char *rgb, int *w, int *h)
{
	char *buffer = NULL;
	fd = settings_read_file(filepath, &buffer);
	
	if (!fd) return;
	
	if (fd[0] == 'P' && fd[1] == '6')
	{
		fd += 2;
		
		//width
		fd = pXm_skip(fd);
		w = atoi(fd);
		while (*fd > ' ') fd++;
		
		//height
		fd = pXm_skip(fd);
		h = atoi(fd);
		while (*fd > ' ') fd++;
		
		//maxval
		fd = pXm_skip(fd);
		int max = atoi(fd);
		while (*fd > ' ') fd++;
		
		if (max != 255 || w<=0 || h<=0)
		{
			free(out_buffer);
			return;
		}
		
		rgb = (unsigned char *)fd;
		
	}
	
	free(buffer);
	
}
