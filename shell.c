#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1000

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t child_pid;
	int status;

	while (1)
	{
		printf("$");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			perror("read error");
			return(1);
		}
		if (line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
			if (strcmp(line, "exit") == 0)
			{
				break;
			}
		}
	}
	char *token;
	char *args[MAX_COMMAND_LENGTH];
	int args_count = 0;

	token = strtok(line, " ");
	while (token != NULL)
	{
		args[args_count] = token;
		args_count++;
		token = strtok(NULL, " ");
	}
	args[args_count] = NULL;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error in fork");
		return(1);
	}
	if (child_pid == 0)
	{
		execve(args[0], args, NULL);
		perror("Execve");
		return(1);
	}
	else
	{
		wait(&status);
		printf("Parent");
	}
	free(line);
	return (0);
}

