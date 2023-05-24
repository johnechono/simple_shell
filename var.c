#include "shell.h"

/**
 * is_chain - chain delimeter
 * @info: parameter
 * @buf: buffer
 * @p:the address of current position
 * Return: 1
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t k = *p;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = k;
	return (1);
}
/**
 * replace_string - replace string
 * @old: address of string
 * @new: new strng
 * Return: 1
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * check_chain -  chaining
 * @info:  parameter
 * @buf: char buff
 * @p: address of current position
 * @i: starting position
 * @len: length of buff
 * Return: null
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[k] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}

	*p = k;
}

/**
 * replace_alias -in the string
 * @info: the parameter
 * Return: 1
 */
int replace_alias(info_t *info)
{
	list_t *nod;
	int j;
	char *q;

	for (j = 0; j < 10; j++)
	{
		nod = node_starts_with(info->alias, info->argv[0], '=');
		if (!nod)
			return (0);
		free(info->argv[0]);
		q = _strchr(nod->str, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		info->argv[0] = q;
	}
	return (1);
}

/**
 * replace_vars - tokenized string
 * @info: parameter
 * Return: 1
 */
int replace_vars(info_t *info)
{
	int j = 0;
	list_t *node;

	for (j = 0; info->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;

		if (!_strcmp(info->argv[j], "$?"))
		{
			replace_string(&(info->argv[j]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[j], "$$"))
		{
			replace_string(&(info->argv[j]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[j][1], '=');
		if (node)
		{
			replace_string(&(info->argv[j]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[j], _strdup(""));

	}
	return (0);
}


