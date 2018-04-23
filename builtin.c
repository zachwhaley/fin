#include "builtin.h"

#include <stdlib.h>

void cmd_exit(char **args)
{
    int code = args[1] ? atoi(args[1]) : 0;
    exit(code);
}
