#include "shell.h"

/**
 * _myenv - prints current environment
 * @infor: Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myenv(infor_t *infor)
{
	print_list_str(infor->env);
	return (0);
}

/**
 * populate_env_list - populates env list
 * @infor: Used to maintain constant function prototype.
 * Return: Always 0
 */
int populate_env_list(infor_t *infor)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	infor->env = node;
	return (0);
}

/**
 * _getenv - gets the value of an environ var
 * @infor: Used to maintain
 * @name: environment variable name
 * Return: value
 */
char *_getenv(infor_t *infor, const char *name)
{
	list_t *node = infor->env;
	char *q;

	while (node)
	{
		q = starts_with(node->str, name);
		if (q && *q)
			return (q);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable
 * @infor: structure containing potential argument
 * Return: Always 0
 */
int _mysetenv(infor_t *infor)
{
	if (infor->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(infor, infor->argv[1], infor->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @infor: Structure containing potential arguments.
 * Return: Always 0
 */
int _myunsetenv(infor_t *infor)
{
	int j;

	if (infor->argc == 1)
	{
		_eputs("Few arguements.\n");
		return (1);
	}
	for (j = 1; j <= infor->argc; j++)
		_unsetenv(info, infor->argv[j]);

	return (0);
}

