#include "shell.h"

/**
 * bfree - frees a pointer and sets address
 * @_ptr: address of free pointer
 * Return: 1
 */
int bfree(void **_ptr)
{
	if (_ptr && *_ptr)
	{
		free(*_ptr);
		*_ptr = NULL;
		return (1);
	}

	return (0);
}

