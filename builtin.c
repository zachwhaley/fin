#include "builtin.h"

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void bltn_exit(char **args);
static void bltn_cd(char **args);
static void bltn_get(char **args);
static void bltn_set(char **args);

struct builtin {
    const char *cmd;
    Builtin func;
};
struct builtin builtins[] = {
    { "exit", bltn_exit },
    { "cd",   bltn_cd },
    { "get",  bltn_get },
    { "set",  bltn_set },
    // End of builtins
    { '\0', NULL }
};

Builtin find_builtin(const char *cmd)
{
    int i;
    for (i = 0; builtins[i].cmd; i++) {
        if (0 == strcmp(builtins[i].cmd, cmd)) {
            break;
        }
    }
    return builtins[i].func;
}

static void bltn_exit(char **args)
{
    int code = args[1] ? atoi(args[1]) : 0;
    exit(code);
}

static void bltn_cd(char **args)
{
    char *dir = args[1] ?: getenv("HOME");
    if (dir) {
        chdir(dir);
    }
}

static void bltn_get(char **args)
{
    for (int i = 1; args[i]; i++) {
        char *val = getenv(args[i]);
        printf("%s = %s\n", args[i], val ?: "");
    }
}

static void bltn_set(char **args)
{
    for (int i = 1; args[i]; i++) {
        char *name = args[i];
        char *val = strchr(name, '=');
        *val++ = '\0';
        setenv(name, val, 1);
    }
}
