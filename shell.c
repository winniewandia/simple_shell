#include "shell.h"

/**
 * create_shdata - initialize the shell data
 * @env: Environment variables
 *
 * Return: Shell structure
 */
shdata_t *create_shdata(char **env)
{
	shdata_t *shell_data = malloc(sizeof(shdata_t));

	if (shell_data == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	shell_data->user_input = NULL;
	shell_data->interactive_mode = isatty(STDIN_FILENO);
	shell_data->line_number = 0;
	shell_data->command = NULL;
	shell_data->cmd_path = NULL;
	shell_data->env = env;
	return (shell_data);
}

/**
 * free_shdata - frees the user input
 * @shell_data: Shell structure
 */
void free_shdata(shdata_t *shell_data)
{
	_free((void **)&shell_data->user_input);
	_free((void **)&shell_data->command);
	free(shell_data);
}

/**
 * tokenize - tokenizes the user input
 * @shell_data: The data of the structure
 * @old_cmd: Old command
 */

void tokenize(shdata_t *shell_data, unsigned int *old_cmd)
{
	char *input_cpy, *token;
	int i = 0, argc = 0;
	unsigned int new_cmd;
	char **cmd;

	input_cpy = _strdup(shell_data->user_input);
	if (input_cpy == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	token = strtok(input_cpy, " \t\n");
	while (token != NULL)
	{
		argc++;
		token = strtok(NULL, " \t\n");
	}
	new_cmd = (argc + 1) * (sizeof(char *));
	cmd = _realloc(shell_data->command, *old_cmd, new_cmd);
	if (cmd == NULL)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	shell_data->command = cmd;
	*old_cmd = new_cmd;
	token = strtok(shell_data->user_input, " \t\n");
	while (token)
	{
		shell_data->command[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	shell_data->command[i] = NULL;
	free(input_cpy);
}

/**
 * shell - simple UNIX command interpretor
 * @input_file: Input file to be read
 * @prog_name: Program name to be printed on error
 * @env: Environment variables
 *
 * Return: 1 if success and NULL otherwise
 */

int shell(char *prog_name, FILE *input_file, char **env)
{
	unsigned int prev_cmd_size = 0;
	shdata_t *shell_data;
	char prompt[] = "$ ";
	size_t len = 0;
	int value = 0;

	shell_data = create_shdata(env);
	if (shell_data == NULL)
	{
		perror("shell data");
		return (-1);
	}
	while (1)
	{
		shell_data->line_number++;
		if (shell_data->interactive_mode)
		{
			write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
		}
		errno = 0;
		if (getline(&shell_data->user_input, &len, input_file) == -1)
		{
			if (errno == 0 || (errno == ENOTTY && !shell_data->interactive_mode))
				break;
			perror("getline");
			continue;
		}
		tokenize(shell_data, &prev_cmd_size);
		if (shell_data->command == NULL || shell_data->command[0] == NULL)
			continue;
		value = exec_check(shell_data, prog_name);
	}
	free_shdata(shell_data);
	return (value);
}

/**
 * main - runs the shell program
 * @argc: Number of arguments
 * @argv: Pointer to a string of arguments
 * @env: Environment variables
 *
 * Return: Always 0(success)
 */

int main(int argc, char *argv[], char **env)
{
	FILE *input_file;
	char *prog_name = _basename(argv[0]);
	int value = 0;

	if (argc == 1)
	{
		value = shell(prog_name, stdin, env);
	}
	else if (argc == 2)
	{
		input_file = fopen(argv[1], "r");
		if (input_file == NULL)
		{
			perror("fopen");
			exit(EXIT_FAILURE);
		}
		value = shell(prog_name, input_file, env);
		fclose(input_file);
	}
	else
	{
		perror("./hsh");
		exit(EXIT_FAILURE);
	}
	return (value);
}

