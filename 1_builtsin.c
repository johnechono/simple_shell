#include "shell.h"

/**
 * unset_alias - sets alias
 * @strg: alias string
 * @info: parameter
 * Return: 0 or 1
 */
int unset_alias(info_t *info, char *strg)
{
	int ret;
	char *q, d;

	q = _strchr(strg, '=');
	if (!q)
		return (1);
	d = *q;
	*q = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, strg, -1)));
	*q = d;
	return (ret);
}

/**
 * set_alias - sets alias
 * @strg: alias string
 * @info: parameter
 * Return: 0 or 1
 */
int set_alias(info_t *info, char *strg)
{
	char *q;

	q = _strchr(strg, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, strg));

	unset_alias(info, strg);
	return (add_node_end(&(info->alias), strg, 0) == NULL);
}

/**
 * _myhistory - displays the history
 * @info: info
 *  Return: 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * print_alias - prints an alias
 * @node: the node
 * Return: 0 or 1
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
 * _myalias - mimics alias
 * @info: info
 * Return: 0
 */
int _myalias(info_t *info)
{
	int i = 0;
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
	for (i = 1; info->argv[i]; i++)
	{
		q = _strchr(info->argv[i], '=');
	if (q)
		set_alias(info, info->argv[i]);
	else
		print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
