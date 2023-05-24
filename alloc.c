#include "shell.h"

/**
 * _realloc - reallocates the memory block
 * @size_old: size of previous block
 * @size_new: size of new block
 * @pt: the pointer to previous block
 * Return: pointer
 */
void *_realloc(void *pt, unsigned int size_old, unsigned int size_new)
{
	char *q;

	if (!size_new)
		return (free(pt), NULL);
	if (!pt)
		return (malloc(size_new));
	if (size_new == size_old)
		return (pt);

	q = malloc(size_new);
	if (!q)
		return (NULL);

	size_old = size_old < size_new ? size_old : size_new;
	while (size_old--)
		q[size_old] = ((char *)pt)[size_old];
	free(pt);
	return (q);
}
