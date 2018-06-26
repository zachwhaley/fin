#pragma once

#include <string.h>
#include <stdbool.h>

static inline bool streq(const char *lhs, const char *rhs)
{
    return strcmp(lhs, rhs) == 0;
}

static inline void split(char *str, char *out[], char toks[])
{
    int ndx = 0;
    char *sub = strtok(str, toks);
    while (sub) {
        out[ndx++] = sub;
        sub = strtok(NULL, toks);
    }
    out[ndx] = NULL;
}
