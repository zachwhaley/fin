#pragma once

#include <string.h>
#include <stdbool.h>

static inline bool streq(const char *lhs, const char *rhs)
{
    return strcmp(lhs, rhs) == 0;
}
