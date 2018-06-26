#include "execute.h"

#include <unistd.h>
#include <sys/wait.h>

int execute(char *const args[], int out, int in)
{
    pid_t pid = fork();
    if (pid == 0) {
        // Dup and close pipe in child process
        if (out != STDOUT_FILENO) {
            dup2(out, STDOUT_FILENO);
            close(out);
        }
        if (in != STDIN_FILENO) {
            dup2(in, STDIN_FILENO);
            close(in);
        }
        execvp(*args, args);
    }
    else {
        // Close pipe in parent process
        if (out != STDOUT_FILENO)
            close(out);
        if (in != STDIN_FILENO)
            close(in);
    }
    return 0;
}
