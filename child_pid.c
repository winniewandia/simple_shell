#include "shell.h"

extern char **environ;

/**
 * child_pid - creates a child process and runs execve
 * @prog_name: Program name used to run the shell
 */

void child_pid(char *prog_name)
{
	pid_t child_pid;
	int status;

	if (access(command, F_OK) == -1)
	{
		printf("%s: 1: %s: not found\n", prog_name, args[0]);
		return;
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	}
}

