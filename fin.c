#include "builtin.h"
#include "execute.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void read_cmd(char *input, int len)
{
    // Print prompt
    printf("> ");
    fgets(input, len, stdin);
}

void parse_cmd(char *input, char *cmd[])
{
    int ndx = 0;
    char toks[] = {' ', '\n'};
    char *arg = strtok(input, toks);
    while (arg) {
        cmd[ndx++] = arg;
        arg = strtok(NULL, toks);
    }
    cmd[ndx] = NULL;
}

void exec_cmd(char *const cmd[])
{
    int i;
    for (i = 0; builtins[i].name; i++) {
        if (streq(builtins[i].name, cmd[0]))
            break;
    }
    bltn_func builtin = builtins[i].func;

    if (builtin)
        builtin(cmd);
    else
        execute(cmd);
}

int main(int argc, char **argv)
{
    char input[1024];
    char *cmd[128];

    while (true) {
        read_cmd(input, sizeof input);
        parse_cmd(input, cmd);
        exec_cmd(cmd);
    }
}
