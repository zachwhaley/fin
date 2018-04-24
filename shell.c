#include "shell.h"

#include <stdlib.h>
#include <string.h>

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

char** splitpipes(char *cmd)
{
    return split(cmd, "|");
}

char** parsecmd(char *cmd)
{
    return split(cmd, " \n");
}
