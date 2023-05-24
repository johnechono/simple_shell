#include "shell.h"

/**
 **_strchr - locates char in the string
 *@d: char to be found
 *@str: string to be parsed
 *Return: s
 */
char *_strchr(char *str, char d)
{
	do {
		if (*str == d)
		{
			return (str);
		}
	} while (*str++ != '\0');

	return (NULL);
}

/**
 **_strncpy - copies string
 *@src: source of string
 *@n: number of char to copy
 *@dest: destination in which the string is to be copied
 *Return: Concat string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j, l;
	char *t = dest;

	j = 0;
	while (src[j] != '\0' && j < n - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < n)
	{
		l = j;
		while (l < n)
		{
			dest[l] = '\0';
			l++;
		}
	}
	return (t);
}

/**
 **_strncat - concats two strings
 *@n: num of bytes to be used
 *@dest: first string
 *@src: second string
 *Return: concat string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, k = 0;
	char *t = dest;

	while (dest[i] != '\0')
		i++;
	while (src[k] != '\0' && k < n)
	{
		dest[i] = src[k];
		i++;
		k++;
	}
	if (k < n)
		dest[k] = '\0';
	return (t);
}

