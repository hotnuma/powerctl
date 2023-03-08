#include "asound.h"
#include "cpuload.h"
#include "sysidle.h"
#include "dmsg.h"

#include <unistd.h>
#include <stdlib.h>

//#define scard "/proc/asound/card1/pcm0p/sub0/status"

// 16h = 57600s
// / 10 = 5760

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

        //if (_is_running(scard))
        //{
        //    count = 0;
        //    continue;
        //}

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
                return system("systemctl poweroff");
            }

            count = idle;

            continue;
        }
    }

    return 0;
}


