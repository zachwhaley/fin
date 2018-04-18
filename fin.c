#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>
#include <sys/wait.h>

char** parsecmd(char *cmd)
{
    size_t len = 100;
    char **args = malloc(len * sizeof(char*));

    const char tok[] = { ' ', '\n' };

    int ndx = 0;
    char *arg = strtok(cmd, tok);
    while (arg) {
        args[ndx] = arg;
        ndx++;
        if (ndx >= len) {
            len += len;
            args = realloc(args, len * sizeof(char*));
        }
        arg = strtok(NULL, tok);
    }
    args[ndx] = '\0';
    return args;
}

int main(int argc, const char *argv[])
{
    char cmd[BUFSIZ];

    while (true) {
        // Print prompt
        printf("𝆑 ");

        // Get user command
        fgets(cmd, sizeof cmd, stdin);
        char **args = parsecmd(cmd);

        // Run command
        pid_t pid = fork();
        if (pid == 0)
            execvp(cmd, args);
        else
            waitpid(pid, NULL, 0);

        free(args);
    }
    return 0;
}
