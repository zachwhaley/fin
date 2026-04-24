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

        // Look for builtin functions
        int i;
        for (i = 0; builtins[i].name; i++) {
            if (streq(builtins[i].name, args[0]))
                break;
        }
        BuiltinFunc builtin = builtins[i].func;

        /* Pipe and setup STDOUT/STDIN */

        // If there is another command, pipe output to the next command; otherwise pipe output to stdout.
        if (cmds[n+1]) {
            pipe(pipefd);
            out = pipefd[1];
        } else {
            out = STDOUT_FILENO;
        }

        if (builtin) {
            builtin(args, out, in);
        }
        else {
            execute(args, out, in);
        }

        // If there is another command, pipe input to the next command; otherwise pipe input to stdin.
        in = cmds[n+1] ? pipefd[0] : STDIN_FILENO;
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
