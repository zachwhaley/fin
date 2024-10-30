#include "builtin.h"
#include "execute.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>

void read_cmd(char *cmd, int len)
{
    // Print prompt
    printf("𝑓 ");
    fgets(cmd, len, stdin);
}

void exec_cmd(char *cmd)
{
    int in = STDIN_FILENO;
    int out = STDOUT_FILENO;
    int pipefd[2];

    char *cmds[128];
    split(cmd, cmds, "|");

    for (int n = 0; cmds[n]; n++) {
        char *args[128];
        split(cmds[n], args, " \n");

        int i;
        for (i = 0; builtins[i].name; i++) {
            if (streq(builtins[i].name, args[0]))
                break;
        }
        bltn_func builtin = builtins[i].func;

        if (builtin) {
            builtin(args);
        }
        else {
            pipe(pipefd);
            out = cmds[n+1] ? pipefd[1] : STDOUT_FILENO;
            execute(args, out, in);
            in = pipefd[0];
        }
    }
    // Wait for all child processes
    while (wait(NULL) > 0);
}

int main()
{
    char cmd[1024];
    while (true) {
        read_cmd(cmd, sizeof cmd);
        exec_cmd(cmd);
    }
}
