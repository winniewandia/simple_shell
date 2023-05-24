#include "shell.h"

/**
 * _strncat - Concatenates 2 strings with specified no of bytes
 * @dest: String to be added
 * @src: String to be attached
 * @n: Number of bytes to be added
 *
 * Return: The concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int i, j;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	j = 0;
	while (j < n && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
