#include "shell.h"

extern char **environ;

/**
 * child_pid - creates a child process and runs execve
 */

void child_pid(void)
{
	pid_t child_pid;
	int status;

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

