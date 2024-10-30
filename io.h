#pragma once

#include <unistd.h>

static inline void close_pipe(int out, int in)
{
    if (out != STDOUT_FILENO) {
        close(out);
    }
    if (in != STDIN_FILENO) {
        close(in);
    }
}
