#include "shell.h"

/**
 * _free - frees a pointer
 * @ptr: pointer to be freed
 */
void _free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

/**
 * _realloc - returns pointer to a new allocated block
 * @ptr: Pointer to be reallocated
 * @old: Old size
 * @new: New size
 *
 * Return: Pointer to void
 */
void* _realloc(void* ptr, unsigned int old, unsigned int new_size)
{
	void* new_ptr;
	unsigned int copy_size;

	if (old == new_size)
		return (ptr);
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (ptr == NULL)
		return (new_ptr);
	copy_size = old < new_size ? old : new_size;
	_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}
