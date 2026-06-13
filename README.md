# Tee CLI Program

This program is mostly for system programming educational purposes, to learn the internals of the computer system using the linux Operating syste. The `Tee` command reads input from stdin and prints it to the console(stdout) and also writes it to the file that is passed as argument to the command.

## Feature
Four system calls were heavily in use:
- Open() system call
- Close() system call
- Read() system call
- Write() system call

## How to Compile
Make sure you have a compiler like gcc installed on your machine
```bash
gcc -Wall -Wextra tee.c -o tee
```

## How to run
```bash
./tee [-a] <file-name> # Or you can just run the tee command ./tee
```
