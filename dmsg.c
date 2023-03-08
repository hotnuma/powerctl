#include "dmsg.h"

#include <stdio.h>
#include <stdarg.h>

bool _debugmsg = false;

void dbg_enable(bool enable)
{
    _debugmsg = enable;
}

void dbg_print(const char *fmt, ...)
{
    if (!_debugmsg)
        return;

    va_list va;
    va_start(va, fmt);
    vfprintf(stdout, fmt, va);
    va_end(va);

    fprintf(stdout, "\n");
    fflush(stdout);
}


