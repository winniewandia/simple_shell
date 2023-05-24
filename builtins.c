#include "shell.h"

/**
 * _pwd - executes pwd builtin command
 * @shell_data: Shell's data structure
 */
void _pwd(shdata_t *shell_data)
{
	char cwd[PATH_MAX];

	if (_strcmp(shell_data->command[0], "pwd") == 0)
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
 * my_exit - executes exit builtin command
 * @shell_data: Shell's data structure
 */
void my_exit(shdata_t *shell_data)
{
	if (_strcmp(shell_data->command[0], "exit") == 0)
	{
		free_shdata(shell_data);
		exit(EXIT_SUCCESS);
	}
}
/**
 * _env - executes env builtin command
 * @shell_data: Shell's data structure
 */
void _env(shdata_t *shell_data)
{
	char **env;
	int i;
	size_t len;

	env = shell_data->env;
	if (!env)
		return;
	if (_strcmp(shell_data->command[0], "env") == 0)
	{
		for (i = 0; env[i] != NULL; i++)
		{
			len = _strlen(env[i]);
			write(STDOUT_FILENO, env[i], len);
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}

