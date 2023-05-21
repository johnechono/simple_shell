#include "shell.h"

unsigned int sig_flag = 0;

/**
 * sig_handler - takes care of signal interupt
 * @uv: unused signal function prototype variable
 * Return: null
 */
static void sig_handler(int uv)
{
	(void) uv;

	if (sig_flag == 0)
	{
		_puts("\n$ ");
	}
	else
	{
		_puts("\n");
	}
}

/**
 * main - main function for the shell
 * @environment: environmental array
 * @argc: argument count
 * @argv: argument vector
 * Return: exit
 */

int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	unsigned int pipe = 0, j;
	size_t lens_buff = 0;
	vars_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	vars.env = make_env(environment);
	vars.argv = argv;
	signal(SIGINT, sig_handler);
	if (!isatty(STDIN_FILENO))
	pipe = 1;
	if (pipe == 0)
	_puts("$ ");

	for (; getline(&(vars.buffer), &lens_buff, stdin) != -1;)
	{
	sig_flag = 1;
	vars.count++;
	vars.commands = tokenize(vars.buffer, ";");

	j = 0;
	while (vars.commands && vars.commands[j] != NULL)
	{
		vars.av = tokenize(vars.commands[j], "\n \t\r");
		if (vars.av && vars.av[0])
		{
		if (check_for_builtins(&vars) == NULL)
			check_for_path(&vars);
	}
	free(vars.av);
	j++;
	}
	if (pipe == 0)
		_puts("\n");
	free(vars.commands);
	vars.buffer = NULL;
	}

	free_env(vars.env);
	free(vars.buffer);
	exit(vars.status);
}
