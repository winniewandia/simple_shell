#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1000

/**
 * shell - simple UNIX command interpretor
 * @prog_name: Name of the program
 */

void shell(char *prog_name)
{
	char *token, *args[MAX_COMMAND_LENGTH], *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t child_pid;
	int status, args_count = 0;

	while (1)
	{
		printf("%s$", prog_name);
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (feof(stdin))
			{
				printf("\nExiting %s...\n", prog_name);
				break;
			}
			else
			{
				perror("getline");
				exit(EXIT_FAILURE);
			}
		}
		if (read == 1)
			continue;
		line[read - 1] = '\0';
		if (strcmp(line, "exit") == 0)
			break;
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
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			execve(args[0], args, NULL);
			perror("line");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	}
	free(line);
}

/**
 * main - runs the shell program
 * @argc: Number of arguments
 * @argv: Pointer to a string of arguments
 *
 * Return: Always 0(success)
 */

int main(int argc, char *argv[])
{
	char *program_name = basename(argv[0]);
	shell(program_name);
	return (0);
}

