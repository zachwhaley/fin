#include "execute.h"

#include <unistd.h>
#include <sys/wait.h>

int execute(char *const cmd[])
{
    pid_t pid = fork();
    if (pid == 0)
        execvp(*cmd, cmd);
    else
        waitpid(pid, NULL, 0);
    return 0;
}
