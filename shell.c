#include "shell.h"

extern char **environ;
char *args[MAX_COMMAND_LENGTH];
char *line;
int args_count;

/**
 * shell - simple UNIX command interpretor
 * @input_file: Input file to be read
 */

void shell(FILE *input_file)
{
	char *token, prompt[] = "./hsh$ ";
	size_t len = 0;
	ssize_t read;
	pid_t child_pid;
	int status;

	line = NULL;
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
		token = strtok(line, " ");
		for (args_count = 0; token != NULL; args_count++)
		{
			args[args_count] = token;
			token = strtok(NULL, " ");
		}
		args[args_count] = NULL;
		if (_strchr(args[0], '/') == NULL)
		{
			if (is_builtin(args[0]))
			{
				_cd();
				_pwd();
				my_exit();
				continue;
			}
			if (access(args[0], X_OK) == -1)
			{
				printf("1: %s: not found\n", args[0]);
				continue;
			}
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			execve(args[0], args, environ);
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

