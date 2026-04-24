#include "builtin.h"
#include "execute.h"
#include "str.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

bool read_cmd(char *cmd, int len)
{
    // Print prompt
    printf("𝑓 ");
    fflush(stdout);
    char *line = fgets(cmd, len, stdin);
    // If the line is NULL, then the shell has nothing to read and should exit cleanly.  This can happen when CTRL-D is pressed.
    return line != NULL;
}

int parse_redirects(char *args[], int *rd_out, int *rd_in)
{
    int i = 0;
    while (args[i]) {
        if (streq(args[i], "<") || streq(args[i], ">") || streq(args[i], ">>")) {
            // Redirect found, process.
            if (!args[i+1]) {
                fprintf(stderr, "ERROR[%s]: Redirect missing file\n", args[i]);
                return -1;
            }
            char *op = args[i];
            char *file = args[i+1];

            int flags;
            int *target;
            if (streq(op, "<")) {
                flags = O_RDONLY;
                target = rd_in;
            } else if (streq(op, ">")) {
                flags = O_WRONLY | O_CREAT | O_TRUNC;
                target = rd_out;
            } else { // op == ">>"
                flags = O_WRONLY | O_CREAT | O_APPEND;
                target = rd_out;
            }
            *target = open(file, flags, 0644);
            if (*target == -1) {
                perror(file);
                if (*rd_in != -1) close(*rd_in);
                if (*rd_out != -1) close(*rd_out);
                return -1;
            }

            // Shift arguments to remove redirect.
            int j = i;
            do {
                args[j] = args[j+2];
            } while (args[j++]);
        } else {
            // No redirect found, increment to next argument.
            i++;
        }
    }
    return 0;
}

void exec_cmd(char *cmd)
{
    int in = STDIN_FILENO;
    int out = STDOUT_FILENO;
    int pipefd[2];

    char *cmds[128];
    split(cmd, cmds, "|");

    for (int n = 0; cmds[n]; n++) {
        char *args[128];
        split(cmds[n], args, " \n");

        // If no command provided, continue
        if (!args[0]) {
            continue;
        }

        // Look for builtin functions
        int i;
        for (i = 0; builtins[i].name; i++) {
            if (streq(builtins[i].name, args[0])) {
                break;
            }
        }
        BuiltinFunc builtin = builtins[i].func;

        // Parse and set file redirects
        int rd_out = -1, rd_in = -1;
        if (parse_redirects(args, &rd_out, &rd_in) == -1) {
            continue;
        }

        // Pipe and setup STDOUT/STDIN
        // If there is another command, pipe output to the next command; otherwise pipe output to stdout.
        if (cmds[n+1]) {
            pipe(pipefd);
            out = pipefd[1];
        } else {
            out = STDOUT_FILENO;
        }
        // Use redirect output file over pipe/stdout.
        out = rd_out != -1 ? rd_out : out;
        in = rd_in != -1 ? rd_in : in;

        // Execute command
        if (builtin) {
            builtin(args, out, in);
        }
        else {
            execute(args, out, in);
        }

        // If there is another command, pipe input to the next command; otherwise pipe input to stdin.
        if (cmds[n+1]) {
            in = pipefd[0];
        } else {
            in = STDIN_FILENO;
        }
    }
    // Wait for all child processes
    while (wait(NULL) > 0);
}

int main()
{
    char cmd[1024];
    while (read_cmd(cmd, sizeof cmd)) {
        exec_cmd(cmd);
    }
}
