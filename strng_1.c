#include "shell.h"

/**
 *_puts - will print the input
 *@strg: printable string
 * Return: void
 */
void _puts(char *strg)
{
	int j = 0;

	if (!strg)
		return;
	while (strg[j] != '\0')
	{
		_putchar(strg[j]);
		j++;
	}
}

/**
 * _putchar - write to stdout
 * @d: character to be printed
 * Return: 1 o/w -1
 */
int _putchar(char d)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (d != BUF_FLUSH)
	{
		buf[j++] = d;
	}
	return (1);
}

/**
 * _strdup - will duplicate the string
 * @strg: str
 * Return: pointer
 */
char *_strdup(const char *strg)
{
	int leng = 0;
	char *retn;

	if (strg == NULL)
		return (NULL);
	while (*strg++)
		leng++;
	retn = malloc(sizeof(char) * (leng + 1));
	if (!retn)
		return (NULL);
	for (leng++; leng--;)
		retn[leng] = *--strg;
	return (retn);
}

/**
 * _strcpy - copies a string
 * @desti:  destination
 * @srce:  source
 * Return: pointer
 */
char *_strcpy(char *desti, char *srce)
{
	int j = 0;

	if (desti == srce || srce == 0)
	{
		return (desti);
	}
	while (srce[j])
	{
		desti[j] = srce[j];
		j++;
	}
	desti[j] = 0;
	return (desti);
}
