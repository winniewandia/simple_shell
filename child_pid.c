#include "shell.h"

/**
 * exec_check - executes the executables
 * @shell_data: Data structure for shell
 * @prog_name: Program name
 *
 * Return: 1 if Success and NULL otherwise
 */

int exec_check(shdata_t *shell_data, char *prog_name)
{
	char *command_path = NULL, *path = NULL;
	int flag = 0, value = 0;

	if (is_builtin(shell_data->command[0]))
	{
		_env(shell_data);
		my_exit(shell_data);
		return (0);
	}
	if (_strchr(shell_data->command[0], '/') == NULL)
	{
		is_executable(shell_data, &command_path, &flag);
		path = flag ? command_path : NULL;
	}
	else
	{
		path = shell_data->command[0];
	}
	if (access(path, F_OK) != 0 || path == NULL)
	{
		my_printf("%s: 1: %s: command not found\n", prog_name,
				shell_data->command[0]);
		_free((void **)&command_path);
		return (-1);
	}
	value = child_pid(shell_data, path);
	_free((void **)&command_path);
	return (value);
}

/**
 * child_pid - creates a child process and runs execve
 * @shell_data: The shell structure
 * @path: Command path
 *
 * Return: 1 if success and NULL otherwise
 */

int child_pid(shdata_t *shell_data, char *path)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		execve(path, shell_data->command, shell_data->env);
		perror(path);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
		else
		{
			return (-1);
		}
	}
}

