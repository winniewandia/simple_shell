#include "shell.h"

/**
 * is_builtin - checks if a command is builtin
 * @command: The command to be checked
 *
 * Return: True if command is built-in and false otherwise
 */

bool is_builtin(char *command)
{
	char *builtins[] = {"exit", "env"};
	unsigned long int i;

	for (i = 0; i < sizeof(builtins) / sizeof(builtins[0]); i++)
	{
		if (_strcmp(command, builtins[i]) == 0)
		{
			return (true);
		}
	}
	return (false);
}

