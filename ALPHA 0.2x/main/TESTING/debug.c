// debug.c
#include "debug.h"
#include <stdio.h>
#include <stdarg.h>
#include "utils.h"

void dbg_log(const char *fmt, ...)
{
    FILE *f = fopen(path_portableinator("Debug.txt"), "a");
    if (!f) return;

    va_list args;
    va_start(args, fmt);
    vfprintf(f, fmt, args);
    va_end(args);

    fclose(f); // force flush every call, so a crash doesn't eat the buffer
}
