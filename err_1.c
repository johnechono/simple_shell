#include "shell.h"

/**
 * remove_comments - remove comments
 * @buff: address
 * Return: Always 0;
 */
void remove_comments(char *buff)
{
	int j;

	for (j = 0; buff[j] != '\0'; j++)
		if (buff[j] == '#' && (!j || buff[j - 1] == ' '))
		{
			buff[j] = '\0';
			break;
		}
}

/**
 * _erratoi - convert str to an int
 * @g: string
 * Return: 0
 */
int _erratoi(char *g)
{
	int j = 0;
	unsigned long int res = 0;

	if (*g == '+')
		g++;
	for (j = 0;  g[j] != '\0'; j++)
	{
		if (g[j] >= '0' && g[j] <= '9')
		{
			res *= 10;
			res += (g[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - prints  error msg
 * @info: struct info
 * @estrg: string
 * Return: 0
 */
void print_error(info_t *info, char *estrg)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estrg);
}

/**
 * print_d - function prints a decimal
 * @inputs: inputs
 * @fd: the filedescriptor to write
 * Return: char printed
 */
int print_d(int inputs, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (inputs < 0)
	{
		_abs_ = -inputs;
		__putchar('-');
		count++;
	}
	else
		_abs_ = inputs;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - convert number
 * @numb: number
 * @base: the base
 * @flags: arg flags
 * Return: strg
 */
char *convert_number(long int numb, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = numb;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -numb;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
