#pragma once

typedef void (*bltn_func)(char* const[]);

struct Builtin {
    const char *name;
    bltn_func func;
};

extern struct Builtin builtins[];

void bltn_exit(char *const args[]);
void bltn_cd(char *const args[]);
void bltn_get(char *const args[]);
void bltn_set(char *const args[]);
