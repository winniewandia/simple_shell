#include "shell.h"

/**
 * is_executable - checks if a command can
 * be found in the PATH
 * @command: Command to be checked
 *
 * Return: Fullpath if successful and NULL otherwise
 */

char *is_executable(char *command)
{
	char *path, *fullpath, *path_token, *original_path;
	DIR *dirp;
	struct dirent *entry;

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);
	original_path = _strdup(path);
	path_token = strtok(original_path, ":");
	while (path_token != NULL)
	{
		dirp = opendir(path_token);
		if (dirp != NULL)
		{
			while ((entry = readdir(dirp)) != NULL)
			{
				if (_strcmp(entry->d_name, command) == 0)
				{
					fullpath = create_path(path_token, command);
					if (access(fullpath, X_OK) == 0)
					{
						closedir(dirp);
						return (fullpath);
					}
				}
			}
			closedir(dirp);
		}
		path_token = strtok(NULL, ":");
	}
	free(original_path);
	return (NULL);
}

/**
 * create_path - create a full path by concatenating directory
 * and command
 * @dir: Directory
 * @command: Command
 *
 * Return: Full path
 */
char *create_path(const char *dir, char *command)
{
	size_t dir_len = _strlen((char *)dir);
	size_t command_len = _strlen(command);
	size_t path_len = dir_len + command_len + 2;
	char *full_path = malloc(path_len);

	if (full_path == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	snprintf(full_path, path_len, "%s/%s", dir, command);
	return (full_path);
}

