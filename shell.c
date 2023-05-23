#include "shell.h"

char *args[MAX_COMMAND_LENGTH];
char *line;
int args_count;
char *command;
/**
 * shell - simple UNIX command interpretor
 * @input_file: Input file to be read
 * @prog_name: Program name to be printed on error
 */

void shell(char *prog_name, FILE *input_file)
{
	char *token, *command_path, prompt[] = "./hsh$ ";
	size_t len = 0;
	ssize_t read;

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
			command = args[0];
			token = strtok(NULL, " ");
		}
		args[args_count] = NULL;
		if (_strchr(command, '/') == NULL)
		{
			if (is_builtin(args[0]))
			{
				_cd();
				_pwd();
				my_exit();
				_env();
				continue;
			}
			command_path = is_executable(args[0]);
			if (command_path == NULL)
			{
				printf("%s: 1: %s: not found\n", prog_name, args[0]);
				continue;
			}
			command = command_path;
		}
		child_pid(prog_name);
		if (input_file == stdin)
			fflush(stdout);
	}
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
	char *prog_name = basename(argv[0]);

	if (argc == 1)
	{
		shell(prog_name, stdin);
	}
	else if (argc == 2)
	{
		input_file = fopen(argv[1], "r");
		if (input_file == NULL)
		{
			perror("fopen");
			exit(EXIT_FAILURE);
		}
		shell(prog_name, input_file);
		fclose(input_file);
	}
	else
	{
		perror("./hsh");
		exit(EXIT_FAILURE);
	}
	free(line);
	return (0);
}

