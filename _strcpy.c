#include "shell.h"

/**
 * _strcpy - copies the string pointed to by src
 * to the character array pointed to by dest
 * @dest: Destination character array
 * @src: Contents to be copied
 *
 * Return: The pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

