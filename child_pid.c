#include "shell.h"

/**
 * child_pid - creates a child process and runs execve
 * @prog_name: Program name used to run the shell
 * @shell_data: The shell structure
 */

void child_pid(char *prog_name, shdata_t *shell_data)
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
		perror("./hsh");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			fflush(stdout);
		}
		else
		{
			my_printf("%s: %s: command not found\n", prog_name, shell_data->command);
		}
	}
}

