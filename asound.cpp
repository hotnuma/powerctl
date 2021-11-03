#include "asound.h"

#include <stdio.h>
#include <string.h>

#include <print.h>

#define STATE_RUNNING "state: RUNNING"
#define BSIZE 14

bool is_playing(const char *filepath)
{
    char buff[BSIZE + 1];
    buff[0] = '\0';

    FILE *fp = fopen(filepath, "rb");
    if (!fp)
        return false;

    size_t nb = fread(buff, 1, BSIZE, fp);

    if (nb > 0)
    {
        buff[nb] = '\0';

        if (strncmp(buff, STATE_RUNNING, BSIZE) == 0)
        {
            //print("%s %s", filepath, buff);

            fclose(fp);

            return true;
        }
    }

    fclose(fp);

    return false;
}



