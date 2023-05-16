#include <stdio.h>

/**
 * main - Prints arguments without using ac
 * @ac: Number of arguments
 * @av: NULL terminated array of strings
 *
 * Return: Always 0 (success)
 */

int main(int __attribute__ ((unused)) ac, char **av)
{
	int i;

	for (i = 0; av[i] != NULL; i++)
	{
		printf("%s ", av[i]);
	}
	printf("\n");
	return (0);
}

