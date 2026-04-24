#include "builtin.h"

#include "io.h"
#include "str.h"

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Builtin builtins[] = {
    { "exit", "exit [code]",     "Exit the shell with an optional exit code.",                  builtin_exit },
    { "cd",   "cd [dir]",        "Change the current directory. Defaults to $HOME.",            builtin_cd },
    { "get",  "get VAR ...",     "Print the value of one or more environment variables.",       builtin_get },
    { "set",  "set VAR=VAL ...", "Set one or more environment variables.",                      builtin_set },
    { "echo", "echo [args ...]", "Write arguments to standard output.",                         builtin_echo },
    { "help", "help [cmd]",      "List builtin commands, or show help for a specific command.", builtin_help },
    // End of builtins
    { NULL, NULL, NULL, NULL }
};

void builtin_exit(char *const args[], int out, int in)
{
    int code = args[1] ? atoi(args[1]) : 0;
    exit(code);
}

void builtin_cd(char *const args[], int out, int in)
{
    char *dir = args[1] ?: getenv("HOME");
    if (dir) {
        chdir(dir);
    }
    close_pipe(out, in);
}

void builtin_get(char *const args[], int out, int in)
{
    for (int i = 1; args[i]; i++) {
        char *val = getenv(args[i]);
        dprintf(out, "%s", val ?: "");
    }
    close_pipe(out, in);
}

void builtin_set(char *const args[], int out, int in)
{
    for (int i = 1; args[i]; i++) {
        char *name = args[i];
        char *val = strchr(name, '=');
        if (!val) {
            fprintf(stderr, "ERROR[set]: %s missing '='\n", name);
            continue;
        }
        *val++ = '\0';
        setenv(name, val, 1);
    }
    close_pipe(out, in);
}

void builtin_echo(char *const args[], int out, int in)
{
    for (int i = 1; args[i]; i++) {
        dprintf(out, "%s", args[i]);
        if (args[i+1]) {
            dprintf(out, " ");
        }
    }
    dprintf(out, "\n");
    close_pipe(out, in);
}

void builtin_help(char *const args[], int out, int in)
{
    if (args[1]) {
        for (int i = 0; builtins[i].name; i++) {
            if (streq(builtins[i].name, args[1])) {
                dprintf(out, "%s\n  %s\n", builtins[i].usage, builtins[i].desc);
                close_pipe(out, in);
                return;
            }
        }
        dprintf(out, "help: no such builtin: %s\n", args[1]);
    } else {
        for (int i = 0; builtins[i].name; i++) {
            dprintf(out, "%-20s %s\n", builtins[i].usage, builtins[i].desc);
        }
    }
    close_pipe(out, in);
}
