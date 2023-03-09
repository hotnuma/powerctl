#include "asound.h"
#include "cpuload.h"
#include "sysidle.h"
#include "dmsg.h"

#include <unistd.h>
#include <stdlib.h>

// 16 h = 57600 sec = 5700 ticks
// 20 min = 1200 sec = 120 ticks

int main(int argc, char **argv)
{
    int n = 1;

    while (n < argc)
    {
        const char *part = argv[n];

        if (strcmp(part, "-debug") == 0)
        {
            dbg_enable(true);
        }

        ++n;
    }

    int minutes = 20;
    int timeout = minutes * 60;
    int tick = 10;
    double cputh = 10.0;

    int count = 0;
    int idle = 0;

    CStringListAuto *list = cstrlist_new_size(12);
    as_parse_cards(list);

    while (1)
    {
        sleep(tick);

        if (as_is_running(list))
        {
            count = 0;
            continue;
        }

        else if (cpuload() > cputh)
        {
            count = 0;
            continue;
        }

        count += tick;

        dbg_print("count : %d", count);

        if (count > timeout)
        {
            idle = (int) sysidle() / 1000;

            dbg_print("idle % d", idle);

            if (idle >= timeout)
            {
                int ret = system("systemctl poweroff");

                return ret;
            }

            count = idle;

            continue;
        }
    }

    return 0;
}


