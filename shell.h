#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <libgen.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_COMMAND_LENGTH 1000

extern char *args[MAX_COMMAND_LENGTH];
extern int args_count;
extern char *line;

int _strlen(char *s);
int _strcmp(char *s1, char *s2);
void shell(FILE *input_file);
void _cd(void);
void _pwd(void);
void my_exit(void);
bool is_builtin(const char *command);

#endif