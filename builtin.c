#include "shell.h"

/**
 * _env - shows the current environment where the shell runs
 * @vars: struct of variables for the program's data
 *
 * Return: nothing
 */
void _env(vars_t *vars)
{
	unsigned int j;

	for (j = 0; vars->env[j]; j++)
	{
		_puts(vars->env[j]);
		_puts("\n");
	}
	vars->status = 0;
}

/**
 * check_for_builtins - checks if the command is a builtin
 * @vars: variables for the program's data
 *
 * Return: pointer to the function or NULL otherwise
 */
void (*check_for_builtins(vars_t *vars))(vars_t *vars)
{
	unsigned int j;
	builtin_t check[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (j = 0; check[j].f != NULL; j++)
	{
		if (_strcmpr(vars->av[0], check[j].name) == 0)
			break;
	}
	if (check[j].f != NULL)
		check[j].f(vars);
	return (check[j].f);
}

/**
 * new_exit - exit of the program with the status
 * @vars: variables for the program's data
 *
 * Return: nothing
 */
void new_exit(vars_t *vars)
{
	int status;

	if (_strcmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		status = _atoi(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			print_error(vars, ": Illegal number: ");
			_puts2(vars->av[1]);
			_puts2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->status = status;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_env(vars->env);
	exit(vars->status);
}

/**
 * new_setenv - create or edit a new environment or existing variable
 * @vars: pointer to struct of variables for the program's data
 * Return: nothing
 */
void new_setenv(vars_t *vars)
{
	char *var;
	char **key;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		print_error(vars, ": incorrect numbers of argument\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
		add_key(vars);
	else
	{
		var = add_value(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			print_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			free_env(vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->status = 0;
}

/**
 * new_unsetenv - remove an environment variable
 * @vars: pointer to a struct of variables for the program's data
 *
 * Return: nothing
 */
void new_unsetenv(vars_t *vars)
{
	char **key, **newenv;

	unsigned int j, k;

	if (vars->av[1] == NULL)
	{
		print_error(vars, ": incorrect numbers of argument\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
	{
		print_error(vars, ": No variable to unset");
		return;
	}
	for (j = 0; vars->env[j] != NULL; j++)
		;
	newenv = malloc(sizeof(char *) * j);
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (j = 0; vars->env[j] != *key; j++)
		newenv[j] = vars->env[j];
	for (k = j + 1; vars->env[k] != NULL; k++, j++)
		newenv[j] = vars->env[k];
	newenv[j] = NULL;
	free(*key);
	free(vars->env);
	vars->env = newenv;
	vars->status = 0;
}
