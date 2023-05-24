#include "shell.h"

/**
 * check_chain - check the chain
 * @buff: character buffer
 * @q: current buff positn
 * @j: buffer strating point
 * @leng: buffer length
 * @info: struct parameter
 * Return: nothing
 */
void check_chain(info_t *info, char *buff, size_t *q, size_t j, size_t leng)
{
	size_t k = *q;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[j] = 0;
			k = leng;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[j] = 0;
			k = leng;
		}
	}
	*q = k;
}

/**
 * is_chain - tests for chain delimiter
 * @info: struct parameter
 * @buff: character buffer
 * @q: positional address
 * Return: 1 o/w 0
 */
int is_chain(info_t *info, char *buff, size_t *q)
{
	size_t k = *q;

	if (buff[k] == '|' && buff[k + 1] == '|')
	{
		buff[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[k] == '&' && buff[k + 1] == '&')
	{
		buff[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[k] == ';')
	{
		buff[k] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = k;
	return (1);
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: struct parameter
 * Return: 1 o/w 0
 */
int replace_alias(info_t *info)
{
	int j;
	char *q;
	list_t *nod;

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
 * replace_vars - var replacement
 * @info: struct parameter
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int j = 0;
	list_t *nod;

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
		nod = node_starts_with(info->env, &info->argv[j][1], '=');
		if (nod)
		{
			replace_string(&(info->argv[j]),
				_strdup(_strchr(nod->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[j], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - will replace string
 * @new: the new string
 * @old: the old string
 * Return: 1 o/w 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
