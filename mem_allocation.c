#include "shell.h"

/**
 * _realloc - will reallocate the pointer
 * @ptr: pointer
 * @size: pointer of elements in the previous array
 * Return: pointer
 */

char **_realloc(char **ptr, size_t *size)
{
	size_t j;
	char **new;

	new = malloc(sizeof(char *) * ((*size) + 10));
	for (j = 0; j < (*size); j++)
	{
		new[j] = ptr[j];
	}
	if (new == NULL)
	{
		free(ptr);
		return (NULL);
	}
	*size += 10;
	free(ptr);
	return (new);
}
