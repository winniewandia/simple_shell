#include "shell.h"

/**
 * is_executable - checks if a command can
 * be found in the PATH
 * @shell_data: Structure of the shell
 * @full_path: Fullpath for the command
 * @flag: Checks if fullpath is found
 */

void is_executable(shdata_t *shell_data, char **full_path, int *flag)
{
	char *path, *path_token, *original_path, *copy;
	unsigned int current = 0, previous = 0;

	path = getenv("PATH");
	if (path == NULL)
		return;
	original_path = _strdup(path);
	if (original_path == NULL)
	{
		perror("strdup");
		return;
	}
	path_token = strtok(original_path, ":");
	while (path_token != NULL)
	{
		current = (_strlen(shell_data->command[0]) +
				strlen(path_token) + 2) * sizeof(char);
		copy = _realloc(*full_path, previous, current);
		if (copy == NULL)
		{
			perror("realloc");
			_free((void **)&original_path);
			return;
		}
		*full_path = copy;
		_strcpy(*full_path, path_token);
		_strcat(*full_path, "/");
		_strcat(*full_path, shell_data->command[0]);
		if (access(*full_path, X_OK) == 0)
		{
			*flag = 1;
			break;
		}
		previous = current;
		path_token = strtok(NULL, ":");
	}
	_free((void **)&original_path);
}

