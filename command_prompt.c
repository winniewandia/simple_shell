#include <stdio.h>
#include <stdlib.h>

/**
 * main - Prints user input
 *
 * Return: Always 0 (success)
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	printf("$ ");
	read = getline(&line, &len, stdin);

	if (read != -1)
	{
		printf("%s", line);
	}
	else
	{
		printf("error");
	}
	free(line);
	return (0);
}

