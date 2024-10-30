#pragma once

typedef void (*BuiltinFunc)(char *const args[], int out, int in);

struct Builtin {
    const char *name;
    BuiltinFunc func;
};

extern struct Builtin builtins[];

void builtin_exit(char *const args[], int out, int in);
void builtin_cd(char *const args[], int out, int in);
void builtin_get(char *const args[], int out, int in);
void builtin_set(char *const args[], int out, int in);
