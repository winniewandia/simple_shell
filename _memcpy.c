#include "shell.h"

/**
 * _memcpy - copies n bytes from src to dest
 * @dest: bytes copied from src
 * @src: string to be copied
 * @n: no of bytes to be copied
 *
 * Return: Copied string
 */

char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

