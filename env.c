#include "shell.h"

/**
 * _myenv - prints current environment
 * @inf: maintain constant function
 * Return: 0
 */
int _myenv(info_t *inf)
{
	print_list_str(inf->env);
	return (0);
}

/**
 * populate_env_list - populate the env list
 * @inf: maintain constant function prototype.
 * Return: 0
 */
int populate_env_list(info_t *inf)
{
	list_t *node = NULL;
	size_t _j;

	for (_j = 0; environ[_j]; _j++)
		add_node_end(&node, environ[_j], 0);
	inf->env = node;
	return (0);
}

/**
 * _getenv - get the value of an environ var
 * @inf: structure containing argument
 * @name: variable name
 * Return: value
 */
char *_getenv(info_t *inf, const char *name)
{
	list_t *node = inf->env;
	char *_q;

	while (node)
	{
		_q = starts_with(node->str, name);
		if (_q && *_q)
			return (_q);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize new environment variable
 * @inf: structure containing potential argument
 *  Return: 0
 */
int _mysetenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Wrong num of args\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove environment var
 * @inf: Struct containing potential argument
 * Return: 0
 */
int _myunsetenv(info_t *inf)
{
	int j;

	if (inf->argc == 1)
	{
		_eputs("few args.\n");
		return (1);
	}
	for (j = 1; j <= inf->argc; j++)
		_unsetenv(inf, inf->argv[j]);
	return (0);
}
