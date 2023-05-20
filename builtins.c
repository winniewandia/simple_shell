#include "shell.h"

/**
 * _cd - executes cd builtin command
 */

void _cd(void)
{
	const char *home_dir;

	if (_strcmp(args[0], "cd") == 0)
	{
		if (args_count > 1)
		{
			if (chdir(args[1]) != 0)
			{
				perror("cd");
			}
		}
		else
		{
			home_dir = getenv("HOME");
			if (home_dir != NULL)
			{
				if (chdir(home_dir) != 0)
				{
					perror("cd");
				}
			}
			else
			{
				fprintf(stderr, "cd: No home directory found\n");
			}
		}
	}
}
/**
 * _pwd - executes pwd builtin command
 */
void _pwd(void)
{
	char cwd[PATH_MAX];

	if (_strcmp(args[0], "pwd") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			write(STDOUT_FILENO, cwd, _strlen(cwd));
			write(STDOUT_FILENO, "\n", 1);
		}
		else
		{
			perror("getcwd");
		}
	}
}
/**
 * _exit - executes exit builtin command
 */
void my_exit(void)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
}

