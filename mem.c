#include "shell.h"

/**
 * bfree - will void the address and free the pointer
 * @pntr: pointer address
 * Return: 1 O/W 0
 */
int bfree(void **pntr)
{
	if (pntr && *pntr)
	{
		free(*pntr);
		*pntr = NULL;
		return (1);
	}

	return (0);
}
