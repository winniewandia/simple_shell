#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <libgen.h>

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
	int status, args_count;

	while (1)
	{
		printf("%s$ ", prog_name);
		if ((read = getline(&line, &len, stdin)) == -1)
		{
			if (feof(stdin))
			{
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
		for (args_count = 0; token != NULL; args_count++)
		{
			args[args_count] = token;
			token = strtok(NULL, " ");
		}
		args[args_count] = NULL;
		if ((child_pid = fork()) == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			execve(args[0], args, NULL);
			perror("./hsh");
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

int main(int __attribute__ ((unused)) argc, char *argv[])
{
	char *program_name = basename(argv[0]);

	shell(program_name);
	return (0);
}

