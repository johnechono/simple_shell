#include "shell.h"

/**
 * _putfd - writes char to given fd
 * @_fd: file descriptor
 * @_b: char to print
 * Return: On success 1 and -1 on error
 */
int _putfd(char _b, int _fd)
{
	static char buf[WRITE_BUF_SIZE];
	static int j;

	if (_b != BUF_FLUSH)
		buf[j++] = _b;
	if (_b == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(_fd, buf, j);
		j = 0;
	}
	return (1);
}

/**
 * _putsfd - prints input string
 * @st: string to print
 * @fd: file descriptor
 * Return: num of chars
 */
int _putsfd(char *st, int fd)
{
	int j = 0;

	if (!st)
		return (0);
	while (*st)
	{
		j += _putfd(*st++, fd);
	}
	return (j);
}

/**
 * _eputchar - writes the char
 * @d: character to print
 * Return: On success 1. On error, -1
 */
int _eputchar(char d)
{
	static int _j;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || _j >= WRITE_BUF_SIZE)
	{
		write(2, buf, _j);
		_j = 0;
	}
	if (d != BUF_FLUSH)
		buf[_j++] = d;
	return (1);
}

/**
 * _eputs - prints an input string
 * @st: string to be printed
 * Return: null
 */
void _eputs(char *st)
{
	int _j = 0;

	if (!st)
	{
		return;
	}
	while (st[_j] != '\0')
	{
		_eputchar(st[_j]);
		_j++;
	}
}
