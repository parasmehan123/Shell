# Shell
## Introduction
* This repository contains the implementation of a Unix Shell in C programming Language.
* By default, the shell program waits for user input from the stdin.
* After the user enters some command, the shell program parses the input to interpret I/O redirection, pipe, etc.
* After interpreting the command as described below, the shell program again waits for user input until the user enters the exit command.
* Shell is also designed to handle nested commands like "/bin/ls | /bin/sort | /bin/uniq | /usr/bin/wc -l 2>&1 1>output.txt". 

## Features Implemented
| Syntax               | Meaning                                                                                                                                   |
|:---------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------|
| command              | Executes the command and wait for the command to finish, it prints error message if the command is invalid.                               |
| command  >  filename | Redirects the stdout to file "filename". If the file does not exists, it creates a new one, otherwise, shell overwrites the existing file |
| 1 > filename         | Redirects stdout to filename                                                                                                              |
| 2 > filename         | Redirect stderr to the filename                                                                                                           |
| command  <  filename | Use file descriptor 0 (stdin) for "filename". If command tries to read from stdin, effectively it will read from filename.                |
| exit                 | Exit from the shell program                                                                                                               |

## Steps to Compile and Run this shell
1. Clone The Repository.
```bash
https://github.com/parasmehan123/Shell.git
```
2. Change directory to Shell.
```bash
cd Shell
```
3. Run the command to compile the shell.c file.
```bash
gcc shell.c -o shell
```
4. Run the executable generated.
```
./shell
```
