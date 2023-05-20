#include "shell.h"

/**
 * print_error - prints the error message
 * @msg: messages to printed
 * @vars: struct pointer
 * Return: null
 */
void print_error(vars_t *vars, char *msg)
{
	char *count;

	_puts2(vars->argv[0]);
	_puts2(": ");
	count = _uitoa(vars->count);
	_puts2(count);
	free(count);
	_puts2(": ");
	_puts2(vars->av[0]);
	if (msg)
	{
		_puts2(msg);
	}
	else
		perror("");
}

/**
 * _puts2 - print standard error
 * @str: printable string
 * Return: null
 */
void _puts2(char *str)
{
	ssize_t nums, lens;

	nums = _strlen(str);
	lens = write(STDERR_FILENO, str, nums);
	if (lens != nums)
	{
		perror("Error");
		exit(1);
	}
}

/**
 * _uitoa - convert unsigned int to string
 * @count: unsigned int to change
 * Return: pointer to string
 */
char *_uitoa(unsigned int count)
{
	unsigned int temp, digit;
	char *num_str;

	temp = count;
	for (digit = 0; temp != 0; digit++)
		temp /= 10;
	num_str = malloc(sizeof(char) * (digit + 1));
	if (num_str == NULL)
	{
		perror("Error_1");
		exit(127);
	}
	num_str[digit] = '\0';
	for (--digit; count; --digit)
	{
		num_str[digit] = (count % 10) + '0';
		count /= 10;
	}
	return (num_str);
}
