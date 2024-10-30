#include "execute.h"

#include "io.h"

#include <unistd.h>
#include <sys/wait.h>

int execute(char *const args[], int out, int in)
{
    pid_t pid = fork();
    if (pid == 0) {
        // Duplicate and close pipe in child process
        if (out != STDOUT_FILENO) {
            dup2(out, STDOUT_FILENO);
        }
        if (in != STDIN_FILENO) {
            dup2(in, STDIN_FILENO);
        }
        close_pipe(out, in);
        execvp(*args, args);
    }
    else {
        // Close pipe in parent process
        close_pipe(out, in);
    }
    return 0;
}
