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
 * @input_file: Input file to be read
 */

void shell(FILE *input_file)
{
	char *token, *args[MAX_COMMAND_LENGTH], *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t child_pid;
	int status, args_count;
	char prompt[] = "./hsh$ ";

	while (1)
	{
		write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
		read = getline(&line, &len, input_file);
		if (read == -1)
		{
			if (feof(input_file))
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
		child_pid = fork();
		if (child_pid == -1)
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
		if (input_file == stdin)
		{
			fflush(stdout);
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
	FILE *input_file;

	if (argc == 1)
	{
		shell(stdin);
	}
	else if (argc == 2)
	{
		input_file = fopen(argv[1], "r");
		if (input_file == NULL)
		{
			perror("fopen");
			exit(EXIT_FAILURE);
		}
		shell(input_file);
		fclose(input_file);
	}
	else
	{
		perror("./hsh");
		exit(EXIT_FAILURE);
	}
	return (0);
}

