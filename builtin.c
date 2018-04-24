#include "builtin.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void cmd_exit(char **args)
{
    int code = args[1] ? atoi(args[1]) : 0;
    exit(code);
}

void cmd_cd(char **args)
{
    if (args[1]) {
        chdir(args[1]);
    }
}

void cmd_get(char **args)
{
    for (int i = 1; args[i]; i++) {
        char *val = getenv(args[i]);
        printf("%s = %s\n", args[i], val ?: "");
    }
}

void cmd_set(char **args)
{
    for (int i = 1; args[i]; i++) {
        char *name = args[i];
        char *val = strchr(name, '=');
        *val++ = '\0';
        setenv(name, val, 1);
    }
}
