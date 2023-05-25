#include "shell.h"

/**
 * *_strchr - locates a character
 * @d: char to look for
 * @t: string passed
 * Return: s
 */
char *_strchr(char *t, char d)
{
	do {
		if (*t == d)
		{
			return (t);
		}
	} while (*t++ != '\0');

	return (NULL);
}

/**
 * *_strncpy - will copy the str
 * @desti: destination str to be copied
 * @o: the amount of char to copy
 * @srce: source of the string
 * Return: concat string
 */
char *_strncpy(char *desti, char *srce, int o)
{
	int j, k;
	char *t = desti;

	j = 0;
	while (srce[j] != '\0' && j < o - 1)
	{
		desti[j] = srce[j];
		j++;
	}
	if (j < o)
	{
		k = j;
		while (k < o)
		{
			desti[k] = '\0';
			k++;
		}
	}
	return (t);
}

/**
 * *_strncat - will concatenate the string
 * @desti: first string
 * @srce: second string
 * @n: the amount of bytes to use
 * Return: concat string
 */
char *_strncat(char *desti, char *srce, int n)
{
	int j, k;
	char *t = desti;

	j = 0;
	k = 0;
	while (desti[j] != '\0')
		j++;
	while (srce[k] != '\0' && k < n)
	{
		desti[j] = srce[k];
		j++;
		k++;
	}
	if (k < n)
		desti[j] = '\0';
	return (t);
}
