#include "shell.h"

/**
 *_atoi - converts string to an int
 *@d: the string to be converted
 *Return: 0
 */

int _atoi(char *d)
{
	int j, sign = 1, flg = 0, out;
	unsigned int res = 0;

	for (j = 0;  d[j] != '\0' && flg != 2; j++)
	{
		if (d[j] == '-')
			sign *= -1;

		if (d[j] >= '0' && d[j] <= '9')
		{
			flg = 1;
			res *= 10;
			res += (d[j] - '0');
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
 * is_delimit - checks if the char is  delimeter
 * @delimit: delimit string
 * @b: char checker
 * Return: 1 if true
 * O/W: 0
 */
int is_delimit(char b, char *delimit)
{
	while (*delimit)
		if (*delimit++ == b)
		{
			return (1);
		}
	return (0);
}

/**
 * _isalphab - checks for alphabetic character
 * @a: The character to input
 * Return: 1
 * O/W: 0
 */

int _isalphab(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}
