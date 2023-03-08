#ifndef ASOUND_H
#define ASOUND_H

#include <cstringlist.h>

int as_parse_cards(CStringList *list);
bool as_is_running(CStringList *list);

bool _is_running(const char *filepath);

#endif // ASOUND_H


