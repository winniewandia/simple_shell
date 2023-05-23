#include "shell.h"

/**
 * _basename - prints the name of file from a path
 * @path: Path to find filename
 */

const char* _basename(const char* path)
{
	const char* filename = path + _strlen((char *) path) - 1;

	while (filename > path && *filename != '\\' && *filename != '/')
	{
		filename--;
	}
	if (*filename == '\\' || *filename == '/')
		filename++;
	return filename;
}

