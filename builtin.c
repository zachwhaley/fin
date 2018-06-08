#include "builtin.h"

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Builtin builtins[] = {
    { "exit", bltn_exit },
    { "cd",   bltn_cd },
    { "get",  bltn_get },
    { "set",  bltn_set },
    // End of builtins
    { '\0', NULL }
};

void bltn_exit(char *const args[])
{
    int code = args[1] ? atoi(args[1]) : 0;
    exit(code);
}

void bltn_cd(char *const args[])
{
    char *dir = args[1] ?: getenv("HOME");
    if (dir) {
        chdir(dir);
    }
}

void bltn_get(char *const args[])
{
    for (int i = 1; args[i]; i++) {
        char *val = getenv(args[i]);
        printf("%s = %s\n", args[i], val ?: "");
    }
}

void bltn_set(char *const args[])
{
    for (int i = 1; args[i]; i++) {
        char *name = args[i];
        char *val = strchr(name, '=');
        *val++ = '\0';
        setenv(name, val, 1);
    }
}
