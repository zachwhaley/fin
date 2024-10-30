#pragma once

typedef void (*BuiltinFunc)(char *const args[]);

struct Builtin {
    const char *name;
    BuiltinFunc func;
};

extern struct Builtin builtins[];

void builtin_exit(char *const args[]);
void builtin_cd(char *const args[]);
void builtin_get(char *const args[]);
void builtin_set(char *const args[]);
