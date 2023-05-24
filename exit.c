#include "shell.h"

/**
 * *_strchr - locates a character
 * @c: char to look for
 * @s: string passed
 * Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * *_strncpy - copies a str
 * @dest: destination str to be copied
 * @n: amount of char to be copied
 * @src: the source string
 * Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j, k;
	char *s = dest;

	j = 0;
	while (src[j] != '\0' && j < n - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < n)
	{
		k = j;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 * *_strncat - concatenates strings
 * @dest: first string
 * @src: second string
 * @m: amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int m)
{
	int j, k;
	char *s = dest;

	j = 0;
	k = 0;
	while (dest[j] != '\0')
		j++;
	while (src[k] != '\0' && k < m)
	{
		dest[j] = src[k];
		j++;
		k++;
	}
	if (k < m)
		dest[j] = '\0';
	return (s);
}
