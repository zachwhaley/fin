#include "builtin.h"

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fin_exit(char **args)
{
    int code = args[1] ? atoi(args[1]) : 0;
    exit(code);
}

void fin_cd(char **args)
{
    char *dir = args[1] ?: getenv("HOME");
    if (dir) {
        chdir(dir);
    }
}

void fin_get(char **args)
{
    for (int i = 1; args[i]; i++) {
        char *val = getenv(args[i]);
        printf("%s = %s\n", args[i], val ?: "");
    }
}

void fin_set(char **args)
{
    for (int i = 1; args[i]; i++) {
        char *name = args[i];
        char *val = strchr(name, '=');
        *val++ = '\0';
        setenv(name, val, 1);
    }
}
