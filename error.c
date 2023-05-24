#include "shell.h"

/**
 * _putfd - puts fd
 * @d: printable character
 * @fd: written file descriptor
 * Return: 1 or -1
 */
int _putfd(char d, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (d != BUF_FLUSH)
		buf[j++] = d;
	return (1);
}

/**
 *_putsfd - writes char to given fd
 * @strg: string to be printed
 * @fd: file descriptor
 * Return: the number of chars put
 */
int _putsfd(char *strg, int fd)
{
	int j = 0;

	if (!strg)
		return (0);
	while (*strg)
	{
		j += _putfd(*strg++, fd);
	}
	return (j);
}

/**
 *_eputs - prints an input string
 * @strg: string to be printed
 * Return: Nothing
 */
void _eputs(char *strg)
{
	int j = 0;

	if (!strg)
		return;
	while (strg[j] != '\0')
	{
		_eputchar(strg[j]);
		j++;
	}
}

/**
 * _eputchar - writes the char
 * @d: character to print
 * Return: On success 1.
 * On error, -1 is returned
 */
int _eputchar(char d)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (d != BUF_FLUSH)
		buf[j++] = d;
	return (1);
}
