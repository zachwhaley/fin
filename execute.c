#include "execute.h"

#include <unistd.h>
#include <sys/wait.h>

int execute(char *const args[])
{
    pid_t pid = fork();
    if (pid == 0)
        execvp(*args, args);
    else
        waitpid(pid, NULL, 0);
    return 0;
}
