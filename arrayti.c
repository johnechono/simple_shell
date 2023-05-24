#include "shell.h"

/**
 * _isalpha - checks for alphabetic character
 * @b: character input
 * Return: 1
 * O/W: 0
 */

int _isalpha(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts string to an int
 * @a: string to change
 * Return: 0
 */

int _atoi(char *a)
{
	unsigned int res = 0;
	int j, sign = 1, flg = 0, out;

	for (j = 0; a[j] != '\0' && flg != 2; j++)
	{
		if (a[j] == '-')
			sign *= -1;

		if (a[j] >= '0' && a[j] <= '9')
		{
			flg = 1;
			res *= 10;
			res += (a[j] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sign == -1)
		out = -res;
	else
		out = res;
	return (out);
}

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 * Return: 1
 * O/W: 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if the char is delimeter
 * @delim: delim string
 * @c: char checker
 * Return: 1 if true
 * O/W: 0
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
		{
			return (1);
		}
	return (0);
}

