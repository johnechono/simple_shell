#include "shell.h"

/**
 *_atoi - converts string to an int
 *@s: the string to be converted
 *Return: 0
 */

int _atoi(char *s)
{
	int j, sign = 1, flg = 0, out;
	unsigned int res = 0;

	for (j = 0;  s[j] != '\0' && flg != 2; j++)
	{
		if (s[j] == '-')
			sign *= -1;

		if (s[j] >= '0' && s[j] <= '9')
		{
			flg = 1;
			res *= 10;
			res += (s[j] - '0');
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
 * is_delim - checks if the char is  delimeter
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

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1
 * O/W: 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
