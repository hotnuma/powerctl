/* SPDX-License-Identifier: GPL-2.0-only
*
* This program prints the "idle time" of the user to stdout.  The "idle time"
* is the number of milliseconds since input was received on any input device.
* If unsuccessful, the program prints a message to stderr and exits with a
* non-zero exit code.
*
* Copyright (c) 2005, 2008 Magnus Henoch <henoch@dtek.chalmers.se>
* Copyright (c) 2006, 2007 by Danny Kukawka <dkukawka@suse.de>,
*                                           <danny.kukawka@web.de>
* Copyright (c) 2008 Eivind Magnus Hvidevold <hvidevold@gmail.com>
* Copyright (c) 2014-2020 Richard Leitner <dev@g0hl1n.net>
*
* This file is part of xprintidle.
*
* xprintidle is free software; you can redistribute it and/or modify it under
* the terms of version 2 of the GNU General Public License as published by the
* Free Software Foundation.
*
* xprintidle is distributed in the hope that it will be useful, but WITHOUT ANY
* WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
* A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* xprintidle. If not, see <https://www.gnu.org/licenses/>.
*
* The function workaroundCreepyXServer was adapted from kpowersave-0.7.3 by
* Eivind Magnus Hvidevold <hvidevold@gmail.com>. kpowersave is licensed under
* the GNU GPL, version 2 _only_.
*/

#include "sysidle.h"

#include <X11/Xlib.h>
#include <X11/extensions/dpms.h>
#include <X11/extensions/scrnsaver.h>
#include <stdio.h>
#include <string.h>

//#ifndef XPRINTIDLE_VERSION
//#define XPRINTIDLE_VERSION "n/a"
//#endif

unsigned long sysidle()
{
    unsigned long idle = 0;

    Display *dpy = XOpenDisplay(nullptr);
    if (!dpy)
    {
        //fprintf(stderr, "couldn't open display\n");
        return 0;
    }

    int event_basep;
    int error_basep;

    if (!XScreenSaverQueryExtension(dpy, &event_basep, &error_basep))
    {
        //fprintf(stderr, "screen saver extension not supported\n");
        return 0;
    }

    XScreenSaverInfo *ssi = XScreenSaverAllocInfo();
    if (!ssi)
    {
        //fprintf(stderr, "couldn't allocate screen saver info\n");
        return 0;
    }

    if (!XScreenSaverQueryInfo(dpy, DefaultRootWindow(dpy), ssi))
    {
        //fprintf(stderr, "couldn't query screen saver info\n");
        return 0;
    }

    idle = ssi->idle;

    XFree(ssi);
    XCloseDisplay(dpy);

    return idle;
}


