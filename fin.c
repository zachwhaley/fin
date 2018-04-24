#include "shell.h"
#include "builtin.h"

#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct command builtins[] = {
    { "exit", cmd_exit },
    { "cd",   cmd_cd },
    { "get",  cmd_get },
    { "set",  cmd_set },
    // End of builtins
    { '\0', NULL }
};

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
            char **args = parsecmd(cmds[i]);

            // Run builtin command
            for (int i = 0; builtins[i].cmd; i++) {
                if (strcmp(builtins[i].cmd, args[0]) == 0) {
                    builtins[i].run(args);
                    goto end;
                }
            }

            // Run command
            pid_t pid = fork();
            if (pid == 0)
                execvp(cmd, args);
            else
                waitpid(pid, NULL, 0);
        end:
            for (int i = 0; args[i]; i++)
                free(args[i]);
            free(args);
        }
    }
    return 0;
}
