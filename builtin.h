#ifndef __FIN_BUILTIN_H__
#define __FIN_BUILTIN_H__

struct command {
    const char *cmd;
    void (*run)(char**);
};

void cmd_exit(char **args);
void cmd_cd(char **args);
void cmd_get(char **args);
void cmd_set(char **args);

#endif /* __FIN_BUILTIN_H__ */
