#include "builtin.h"

#include <stdlib.h>
#include <unistd.h>

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
