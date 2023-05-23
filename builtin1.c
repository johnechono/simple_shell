#include "shell.h"

/**
 * find_key - will find the environ variable
 * @env: environmental variable array
 * @key: variable that should be found
 * Return: pointer
 */
char **find_key(char **env, char *key)
{
	unsigned int j, k, lens;

	lens = _strlen(key);
	for (j = 0; env[j] != NULL; j++)
	{
		for (k = 0; k < lens; k++)
			if (key[k] != env[j][k])
				break;
		if (k == lens && env[j][k] == '=')
			return (&env[j]);
	}
	return (NULL);
}

/**
 * add_key - will create a fresh environ variable
 * @vars: variable struct pointer
 * Return: void
 */
void add_key(vars_t *vars)
{
	char **new_env;
	unsigned int j;

	for (j = 0; vars->env[j] != NULL; j++)
		;
	new_env = malloc(sizeof(char *) * (j + 2));
	if (new_env == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (j = 0; vars->env[j] != NULL; j++)
		new_env[j] = vars->env[j];
	new_env[j] = add_value(vars->av[1], vars->av[2]);
	if (new_env[j] == NULL)
	{
		print_error(vars, NULL);
		free(vars->buffer);
		free(vars->av);
		free_env(vars->env);
		free(vars->commands);
		free(new_env);
		exit(127);
	}
	new_env[j + 1] = NULL;
	free(vars->env);
	vars->env = new_env;
}

/**
 * add_value - will create fresh variable
 * @key: name of variable
 * @value: value of the variable
 * Return: pointer or 0 on success
 */
char *add_value(char *key, char *value)
{
	unsigned int lens1, lens2, j, k;
	char *new;

	lens2 = _strlen(value);
	lens1 = _strlen(key);
	new = malloc(sizeof(char) * (lens1 + lens2 + 2));
	if (new == NULL)
		return (NULL);
	for (j = 0; key[j] != '\0'; j++)
		new[j] = key[j];
	new[j] = '=';
	for (k = 0; value[k] != '\0'; k++)
		new[j + 1 + k] = value[k];
	new[j + 1 + k] = '\0';
	return (new);
}

/**
 * _atoi - will convert str to int
 * @str: converted string
 * Return: -1 for error or int value
 */
int _atoi(char *str)
{
	unsigned int j, dig;
	int nums = 0, test_num;

	test_num = INT_MAX;
	for (dig = 0; test_num != 0; dig++)
		test_num /= 10;
	for (j = 0; str[j] != '\0' && j < dig; j++)
	{
		nums *= 10;
		if ((j == dig - 1) && (str[j] - '0' > INT_MAX % 10))
			return (-1);
		if (str[j] < '0' || str[j] > '9')
			return (-1);
		nums += str[j] - '0';
		if ((j == dig - 2) && (str[j + 1] != '\0') && (nums > INT_MAX / 10))
			return (-1);
	}
	if (j > dig)
		return (-1);
	return (nums);
}
