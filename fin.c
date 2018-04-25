#include "shell.h"
#include "builtin.h"

#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, const char *argv[])
{
    char cmd[BUFSIZ];

    while (true) {
        // Print prompt
        printf("$ ");

        // Get user command
        fgets(cmd, sizeof cmd, stdin);

        // Split piped commands
        char **cmds = splitpipes(cmd);
        for (int i = 0; cmds[i]; i++) {
            run_command(cmds[i]);
        }
    }
    return 0;
}
