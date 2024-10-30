# fin /fɪn/

Short for Griffin and pronounced Finn

fin is a simply made Unix shell written in C

## What You Need

[GNU GCC](http://gcc.gnu.org/)

```bash
$ sudo dnf install gcc
```

## What it Does

Navigates the system with `cd`.

Sets and prints environment variables `set` and `get`.

Runs system commands.

Use `exit` command to exit fin.

## How to Use it

```sh
$ make
$ ./fin
𝑓 set fin=cool
𝑓 get fin
cool
𝑓 ls
builtin.c  builtin.h  execute.c  execute.h  fin.c  LICENSE  Makefile  README.md  str.h
𝑓 ls | grep fin
fin.c
𝑓 exit
```
