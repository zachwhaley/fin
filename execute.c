#include "execute.h"

#include "io.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

static const int CMD_NOT_FOUND = 127;

int execute(char *const args[], int out, int in)
{
    pid_t pid = fork();
    if (pid == 0) {
        // Duplicate and close pipe in child process
        duplicate_pipe(out, in);
        close_pipe(out, in);
        execvp(*args, args);
        perror(*args);
        exit(CMD_NOT_FOUND);
    }
    else {
        // Close pipe in parent process
        close_pipe(out, in);
    }
    return 0;
}
