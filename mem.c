#include "shell.h"

/**
 * bfree - will void the address and free the pointer
 * @ptr: pointer address
 * Return: 1 O/W 0
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}

	return (0);
}
