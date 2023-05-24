#include "shell.h"

/**
 * _setenv - Initializes new environment variable
 * @var: string env
 * @info: to maintain a constant function prototype.
 * @value: string env var value
 * Return: 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	list_t *nodde;
	char *buff = NULL;
	char *q;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	nodde = info->env;
	while (nodde)
	{
		q = starts_with(nodde->str, var);
		if (q && *q == '=')
		{
			free(nodde->str);
			nodde->str = buff;
			info->env_changed = 1;
			return (0);
		}
		nodde = nodde->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}

/**
 * get_environ - returns string array copy of environ
 * @info: to maintain constant function prototype
 * Return: 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _unsetenv - remove an environment variable
 * @info: Used to maintain constant function
 *  Return: 1
 *  O/W: 0
 * @var: string env var
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *nodde = info->env;
	char *_q;
	size_t a = 0;

	if (!nodde || !var)
		return (0);

	while (nodde)
	{
		_q = starts_with(nodde->str, var);
		if (_q && *_q == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), a);
			a = 0;
			nodde = info->env;
			continue;
		}
		nodde = nodde->next;
		a++;
	}
	return (info->env_changed);
}
