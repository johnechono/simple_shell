#include "shell.h"

/**
 * free_info - frees info
 * @al: all fields
 * @info: struct
 */
void free_info(info_t *info, int al)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (al)
	{
		if (info->env)
			free_list(&(info->env));
		if (!info->cmd_buf)
			free(info->arg);
		if (info->alias)
			free_list(&(info->alias));
		if (info->history)
			free_list(&(info->history));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * clear_info - initizes info_t struct
 * @info: struct aess
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t
 * @av: argument vector
 * @info: info
 */
void set_info(info_t *info, char **av)
{
	int a = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (a = 0; info->argv && info->argv[a]; a++)
			;
		info->argc = a;

		replace_vars(info);
		replace_alias(info);
	}
}

