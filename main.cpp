#include "cpuload.h"
#include "sysidle.h"

#include <unistd.h>
#include <stdlib.h>
#include <print.h>

int main()
{
    int minutes = 20;
    int tick = 2;

    int timeout = minutes * 60;

    unsigned long cpu = 0;
    int count = 0;
    int idle = 0;

    while (1)
    {
        cpu = cpuload();

        if (cpu > 2)
        {
            count = 0;
        }
        else
        {
            count += tick;

            //print("count : %d, cpu : %lu", count, cpu);

            if (count > timeout)
            {
                idle = (int) sysidle() / 1000;

                //print("idle % d", idle);

                if (idle >= timeout)
                {
                    system("systemctl poweroff");
                    break;
                }

                count = idle;

                sleep(tick);
                continue;
            }
        }

        sleep(tick);
    }

    return 0;
}


