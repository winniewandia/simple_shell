#include "shell.h"

/**
 * _strncpy - Copies one string to another
 * @dest: Where copied characters are to be placed
 * @src: Where characters are to be copied from
 * @n: No of bytes to be copied
 *
 * Return: pointer to destination string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, j;

	i = 0;
	j = 0;
	while (i < n && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	for (; i < n; i++)
	{
		dest[i] = '\0';
	}
	return (dest);
}

