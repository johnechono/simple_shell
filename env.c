#include "shell.h"

/**
 * _myenv - prints current environ
 * @info: info
 * Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * populate_env_list - will populate the env list
 * @info: will maintain function
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
	{
		add_node_end(&node, environ[j], 0);
	}
	info->env = node;
	return (0);
}

/**
 * _getenv - will get the value of the environ
 * @info: info
 * @name: name of the env
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *q;

	while (node)
	{
		q = starts_with(node->str, name);
		if (q && *q)
		{
			return (q);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - my setenv
 * @info: info
 * Return: 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Invalid argument number\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - will remove the unsetenv
 * @info: info
 * Return: 0
 */
int _myunsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("little arguments.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}

