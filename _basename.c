#include "shell.h"

/**
 * _basename - prints the name of file from a path
 * @path: Path to find filename
 *
 * Return: The filename in the path
 */

char *_basename(char *path)
{
	char *filename = path + _strlen(path) - 1;

	while (filename > path && *filename != '\\' && *filename != '/')
	{
		filename--;
	}
	if (*filename == '\\' || *filename == '/')
		filename++;
	return (filename);
}

