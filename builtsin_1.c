#include "shell.h"

/**
 * unset_alias - sets alias
 * @str: alias string
 * @info: parameter
 * Return: Always 0 on success, 1 on error otherwise
 */
int unset_alias(info_t *info, char *str)
{
	int ret;
	char *q, d;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	d = *q;
	*q = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*q = d;
	return (ret);
}

/**
 * set_alias - sets alias
 * @str: alias string
 * @info: parameter
 * Return: Always 0 on success, otherwise 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _myhistory - displays the history list
 * @info: Used to maintain constant function
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * print_alias - prints an alias
 * @node: the node
 * Return: Always 0 on success, otherwise 1 on error
 */
int print_alias(list_t *node)
{
	char *q = NULL;
	char *b = NULL;

	if (node)
	{
		q = _strchr(node->str, '=');
		for (b = node->str; b <= q; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias
 * @info: Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int j = 0;
	char *q = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		q = _strchr(info->argv[j], '=');
	if (q)
		set_alias(info, info->argv[j]);
	else
		print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
