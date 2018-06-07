#pragma once

typedef void (*Builtin)(char**);

Builtin find_builtin(const char *cmd);
