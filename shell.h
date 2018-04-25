#ifndef __FIN_SHELL_H__
#define __FIN_SHELL_H__

struct Builtin {
    const char *cmd;
    void (*run)(char**);
};

struct Builtin* get_builtin(const char *cmd);
void run_command(char *cmd);

char** splitpipes(char *cmd);

#endif /* __FIN_SHELL_H__ */
