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
	const char prompt[] = "#cisfun$ ";
	char *token;
	char *args[MAX_COMMAND_LENGTH];
	int args_count = 0;

	while (1)
	{
		write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (feof(stdin))
			{
				break;
			}
			else
			{
				perror("read error");
				exit(EXIT_FAILURE);
			}
		}
		if (line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
			if (strcmp(line, "exit") == 0)
			{
				break;
			}
			else if (strcmp(line, "") == 0)
			{
				continue;
			}
		}
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
			perror("./hsh");
			return(1);
		}
		else
		{
			wait(&status);
		}
	}
	free(line);
	return (0);
}

