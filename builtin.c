#include "builtin.h"

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Builtin builtins[] = {
    { "exit", builtin_exit },
    { "cd",   builtin_cd },
    { "get",  builtin_get },
    { "set",  builtin_set },
    // End of builtins
    { NULL, NULL }
};

void builtin_exit(char *const args[])
{
    int code = args[1] ? atoi(args[1]) : 0;
    exit(code);
}

void builtin_cd(char *const args[])
{
    char *dir = args[1] ?: getenv("HOME");
    if (dir) {
        chdir(dir);
    }
}

void builtin_get(char *const args[])
{
    for (int i = 1; args[i]; i++) {
        char *val = getenv(args[i]);
        printf("%s = %s\n", args[i], val ?: "");
    }
}

void builtin_set(char *const args[])
{
    for (int i = 1; args[i]; i++) {
        char *name = args[i];
        char *val = strchr(name, '=');
        *val++ = '\0';
        setenv(name, val, 1);
    }
}
