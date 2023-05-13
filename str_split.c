#include <stdio.h>
#include <string.h>

/**
 * main - splits a string and returns an array of each word of the string
 *
 * Return: Always 0 (success)
 */

int main(void)
{
	char str[] = "Hello Charles and Winnie!";

	char *pointer = strtok(str, " !");

	while (pointer != NULL)
	{
		printf("%s\n", pointer);
		pointer = strtok(NULL, " !");
	}
	return (0);
}

