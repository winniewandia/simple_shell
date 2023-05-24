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
#include <dirent.h>
#include <stdarg.h>

#define MAX_COMMAND_LENGTH 1000

extern char *args[MAX_COMMAND_LENGTH];
extern int args_count;
extern char *line;
extern char *command;

int _strlen(char *s);
int _strcmp(char *s1, char *s2);
void shell(char *prog_name, FILE *input_file);
void _cd(void);
void _pwd(void);
void my_exit(void);
void _env(void);
bool is_builtin(const char *command);
char *_strchr(char *s, char c);
char *_strncpy(char *dest, char *src, int n);
char *create_path(const char *dir, char *command);
char *is_executable(char *command);
void child_pid(char *prog_name);
char *_strdup(char *str);
char* _basename(char* path);
int stderror_printf(FILE *stream, const char *str);
char *_strncat(char *dest, char *src, int n);
int _putchar(char c);
void my_printf(const char* format, ...);
#endif
