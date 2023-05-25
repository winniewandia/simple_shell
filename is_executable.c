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
	char *path, *path_token, *original_path, *result = NULL;
	DIR *dirp;
	struct dirent *entry;
	char *fullpath = NULL;

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
						result = _strdup(fullpath);
						closedir(dirp);
						dirp = NULL;
						break;
					}
				}
			}
			if (dirp != NULL)
				closedir(dirp);
		}
		free(fullpath);
		if (result != NULL)
			break;
		path_token = strtok(NULL, ":");
	}
	free(original_path);
	return (result);
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
	char full_path[MAX_COMMAND_LENGTH];

	_strncpy(full_path, (char *)dir, sizeof(full_path));
	_strncat(full_path, "/", sizeof(full_path) - _strlen(full_path) - 1);
	_strncat(full_path, command, sizeof(full_path) - strlen(full_path) - 1);
	return (_strdup(full_path));
}

