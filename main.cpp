#include "cpuload.h"
#include "sysidle.h"
#include "asound.h"

#include <unistd.h>
#include <stdlib.h>

//#define DEBUG
#include <print.h>

#define scard "/proc/asound/card1/pcm0p/sub0/status"

// 16h = 57600s
// / 10 = 5760

int main()
{
    int minutes = 20;

    int timeout = minutes * 60;
    int tick = 10;
    double cputh = 10.0;

    int count = 0;
    int idle = 0;

    while (1)
    {
        sleep(tick);

        if (is_playing(scard))
        {
            //print("playing");

            count = 0;
            continue;
        }

        else if (cpuload() > cputh)
        {
            //print("cpu");

            count = 0;
            continue;
        }

        count += tick;

        dprint("count : %d", count);

        if (count > timeout)
        {
            idle = (int) sysidle() / 1000;

            //print("idle % d", idle);

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


