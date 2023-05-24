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
#include <errno.h>

#define MAX_COMMAND_LENGTH 1000


/**
 * struct shdata - the shell struct data
 * @user_input: What the user inputs
 * @interactive_mode: Checks if it's interactive mode
 * @line_number: Number of lines
 * @command: Command typed by user
 * @env: The environment variables
 * @cmd_path: Path to the executable
 */

typedef struct shdata
{
	char *user_input;
	int interactive_mode;
	unsigned int line_number;
	char **command;
	char **env;
	char *cmd_path;
} shdata_t;

int _strlen(char *s);
int _strcmp(char *s1, char *s2);
void shell(char *prog_name, FILE *input_file, char **env);
void _pwd(shdata_t *shell_data);
void my_exit(shdata_t *shell_data);
void _env(shdata_t *shell_data);
bool is_builtin(char *command);
char *_strchr(char *s, char c);
char *_strncpy(char *dest, char *src, int n);
char *create_path(const char *dir, char *command);
char *is_executable(char *command);
void child_pid(char *prog_name, shdata_t *shell_data);
char *_strdup(char *str);
char* _basename(char* path);
int stderror_printf(FILE *stream, const char *str);
char *_strncat(char *dest, char *src, int n);
int _putchar(char c);
void my_printf(const char* format, ...);
void start_shdata(shdata_t *shell_data, char **env);
void free_shdata(shdata_t *shell_data);
void tokenize(shdata_t *shell_data, unsigned int *old_cmd);
void _free(void **ptr);
char *_memcpy(char *dest, char *src, unsigned int n);
void* _realloc(void* ptr, unsigned int old, unsigned int new_size);
void builtin_exec(shdata_t *shell_data);
void exec_check(shdata_t *shell_data, char *prog_name);

#endif
