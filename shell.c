#include "shell.h"

#include "builtin.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Builtin* get_builtin(const char *cmd)
{
    int ndx;
    for (ndx = 0; builtins[ndx].cmd; ndx++) {
        if (strcmp(builtins[ndx].cmd, args[0]) == 0)
            break;
    }
    return &builtins[ndx];
}

static char** split(char *str, const char *sep)
{
    size_t len;
    char *s = str;
    for (len = 0; s[len]; (s[len] == sep) ? len++ : *s++);

    char **res = calloc(len, sizeof(char*));
    char *arg = strtok(str, sep);
    int ndx = 0;
    while (arg) {
        res[ndx++] = strdup(arg);
        arg = strtok(NULL, sep);
    }
    return res;
}

static char** parsecmd(char *cmd)
{
    return split(cmd, " \n");
}

char** splitpipes(char *cmd)
{
    return split(cmd, "|");
}

void runcommand(char *cmd)
{
    char **args = split(cmd, " \n");

    // Run builtin command

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
