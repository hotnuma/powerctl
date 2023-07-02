#include "asound.h"
#include "dmsg.h"

#include <cdirparser.h>
#include <libstr.h>
#include <stdio.h>
#include <string.h>

#define STATE_RUNNING "state: RUNNING"
#define PART_POS 19
#define BSIZE 14

int as_parse_cards(CStringList *list)
{
    const char *indir = "/proc/asound";

    CDirParserAuto *dir = cdirparser_new();
    if (!cdirparser_open(dir, indir, CDP_FILES | CDP_SUBDIRS))
        return 0;

    CStringAuto *filepath = cstr_new_size(32);
    char part[24];

    while (cdirparser_read(dir, filepath, NULL))
    {
        if (cstr_endswith(filepath, "/status", true))
        {
            if (cstr_size(filepath) < PART_POS)
                continue;

            const char *p = c_str(filepath) + PART_POS;
            const char *end = strchr(p, '/');

            if (!end)
                continue;

            strncpy(part, p, end - p);

            if (str_startswith(part, "pcm", true)
                && str_endswith(part, "p", true))
            {
                dbg_print("list : %s", c_str(filepath));

                cstrlist_append(list, c_str(filepath));
            }
        }
    }

    return cstrlist_size(list);
}

bool as_is_running(CStringList *list)
{
    static int idx;

    int size = cstrlist_size(list);
    if (size < 1)
        return false;

    if (idx + 1 > size)
        idx = 0;

    CString *sndpath = cstrlist_at(list, idx);
    const char *filepath = c_str(sndpath);

    bool ret = (sndpath && _is_running(filepath));

    if (ret)
    {
        dbg_print("running : %s", filepath);
    }
    else
    {
        dbg_print("closed : %s", filepath);

        ++idx;
    }

    return ret;
}

bool _is_running(const char *filepath)
{
    char buff[BSIZE + 1];
    buff[0] = '\0';

    FILE *fp = fopen(filepath, "rb");
    if (!fp)
        return false;

    bool ret = false;
    size_t nb = fread(buff, 1, BSIZE, fp);

    if (nb > 0)
    {
        buff[nb] = '\0';

        if (strncmp(buff, STATE_RUNNING, BSIZE) == 0)
            ret = true;
    }

    fclose(fp);

    return ret;
}


