#include "shell.h"

/**
 * free_info - frees info
 * @all: all fields
 * @infor: struct
 */
void free_info(infor_t *infor, int all)
{
	ffree(infor->argv);
	infor->argv = NULL;
	infor->path = NULL;
	if (all)
	{
		if (!infor->cmd_buf)
			free(infor->arg);
		if (infor->env)
			free_list(&(infor->env));
		if (infor->history)
			free_list(&(infor->history));
		if (infor->alias)
			free_list(&(infor->alias));
		ffree(infor->environ);
			infor->environ = NULL;
		bfree((void **)infor->cmd_buf);
		if (infor->readfd > 2)
			close(infor->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * clear_info - initializes info_t struct
 * @infor: struct address
 */
void clear_info(infor_t *infor)
{
	infor->arg = NULL;
	infor->argv = NULL;
	infor->path = NULL;
	infor->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @av: argument vector
 * @infor: info
 */
void set_info(infor_t *infor, char **av)
{
	int j = 0;

	infor->fname = av[0];
	if (infor->arg)
	{
		infor->argv = strtow(infor->arg, " \t");
		if (!infor->argv)
		{
			infor->argv = malloc(sizeof(char *) * 2);
			if (infor->argv)
			{
				infor->argv[0] = _strdup(infor->arg);
				infor->argv[1] = NULL;
			}
		}
		for (j = 0; infor->argv && infor->argv[j]; j++)
			;
		infor->argc = j;

		replace_alias(infor);
		replace_vars(infor);
	}
}
