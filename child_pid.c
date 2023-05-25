#include "shell.h"

/**
 * builtin_exec - executes the builtins
 * @shell_data: Data structure for shell
 */

void builtin_exec(shdata_t *shell_data)
{
	if (is_builtin(shell_data->command[0]))
	{
		_pwd(shell_data);
		_env(shell_data);
		my_exit(shell_data);
	}
}

/**
 * exec_check - executes the executables
 * @shell_data: Data structure for shell
 * @prog_name: Program name
 */

void exec_check(shdata_t *shell_data, char *prog_name)
{
	char *command_path;

	if (_strchr(shell_data->command[0], '/') == NULL)
	{
		command_path = is_executable(shell_data->command[0]);
		if (command_path == NULL)
		{
			my_printf("%s: No such file or directory\n", prog_name);
			free(shell_data->cmd_path);
			return;
		}
		else
		{
			shell_data->cmd_path = command_path;
		}
	}
	else
	{
		shell_data->cmd_path = shell_data->command[0];
	}
	if (access(shell_data->cmd_path, F_OK) != 0 || shell_data->cmd_path == NULL)
	{
		my_printf("%s: 1: %s: command not found\n", prog_name, shell_data->command);
		_free((void **)&shell_data->cmd_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		child_pid(shell_data);
	}
}

/**
 * child_pid - creates a child process and runs execve
 * @prog_name: Program name used to run the shell
 * @shell_data: The shell structure
 */

void child_pid(shdata_t *shell_data)
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
		execve(shell_data->cmd_path, shell_data->command, shell_data->env);
		perror(shell_data->cmd_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}

