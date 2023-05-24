#include "shell.h"

/**
 **_memset - will fill up the memory with a byte
 *@n: number of byte to fill
 *@s: memory area pointer
 *@b: fill pointer with this byte
 *Return: s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
	{
		s[j] = b;
	}
	return (s);
}

/**
 * _realloc - reallocate memory block
 * @old_size: previous block size
 * @new_size: new block size
 * @ptr: pointer
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *q;

	if (!ptr)
	{
		return (malloc(new_size));
	}
	if (!new_size)
	{
		return (free(ptr), NULL);
	}
	if (new_size == old_size)
	{
		return (ptr);
	}

	q = malloc(new_size);
	if (!q)
	{
		return (NULL);
	}

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		q[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (q);
}

/**
 * ffree - will free the strings
 * @qq: the strings
 */
void ffree(char **qq)
{
	char **b = qq;

	if (!qq)
	{
		return;
	}
	while (*qq)
	{
		free(*qq++);
	}
	free(b);
}
