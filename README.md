# fin /fɪn/

Short for Griffin and pronounced Finn

fin is a simply made Unix shell written in C

## What You Need

[GNU GCC](http://gcc.gnu.org/)

## How to build it

```sh
$ make
```

## What it Does

### Builtin commands

| Command | Usage | Description |
|---------|-------|-------------|
| `cd` | `cd [dir]` | Change the current directory. Defaults to `$HOME`. |
| `echo` | `echo [args ...]` | Write arguments to standard output. |
| `exit` | `exit [code]` | Exit the shell with an optional exit code. |
| `get` | `get VAR ...` | Print the value of one or more environment variables. |
| `help` | `help [cmd]` | List builtin commands, or show help for a specific command. |
| `set` | `set VAR=VAL ...` | Set one or more environment variables. |

### Piping

Connect commands with `|` to pipe the output of one into the input of the next.

### Redirecting

Redirect input and output with `<`, `>`, and `>>`.

## Examples

```sh
$ ./fin
𝑓 set GREETING=hello
𝑓 get GREETING
hello
𝑓 echo fin is cool
fin is cool
𝑓 echo fin is cool > fin.txt
𝑓 echo fin is also fun >> fin.txt
𝑓 cat fin.txt
fin is cool
fin is also fun
𝑓 grep cool < fin.txt
fin is cool
𝑓 ls | grep fin
fin
fin.c
fin.txt
𝑓 exit
```
