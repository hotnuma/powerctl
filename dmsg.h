#ifndef DMSG_H
#define DMSG_H

#include <stdbool.h>

void dbg_enable(bool enable);
void dbg_print(const char *fmt, ...);

#endif // DMSG_H


