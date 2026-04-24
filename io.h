#pragma once

#include <unistd.h>

static inline void duplicate_pipe(int out, int in)
{
    if (out != STDOUT_FILENO) {
        dup2(out, STDOUT_FILENO);
    }
    if (in != STDIN_FILENO) {
        dup2(in, STDIN_FILENO);
    }
}

static inline void close_pipe(int out, int in)
{
    if (out != STDOUT_FILENO) {
        close(out);
    }
    if (in != STDIN_FILENO) {
        close(in);
    }
}
