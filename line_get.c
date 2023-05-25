#include "shell.h"

/**
 * input_buf - function buffer
 * @info: info
 * @buff: buffer
 * @lens: buffer address
 * Return: the byte
 */
ssize_t input_buf(info_t *info, char **buff, size_t *lens)
{
	ssize_t s = 0;
	size_t len_q = 0;

	if (!*lens)
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(buff, &len_q, stdin);
#else
		s = _getline(info, buff, &len_q);
#endif
		if (s > 0)
		{
			if ((*buff)[s - 1] == '\n')
			{
				(*buff)[s - 1] = '\0';
				s--;
			}
			info->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(info, *buff, info->histcount++);
			/* if (_strchr(*buff, ';')) is this a command chain? */
			{
				*lens = s;
				info->cmd_buf = buff;
			}
		}
	}
	return (s);
}

/**
 * sigintHandler - will block copy command
 * @sig_numb: the number signal
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_numb)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * get_input - will get the new input
 * @info: info
 * Return: byte
 */
ssize_t get_input(info_t *info)
{
	static char *buff;
	static size_t j, k, lens;
	ssize_t m = 0;
	char **buff_q = &(info->arg), *q;

	_putchar(BUF_FLUSH);
	m = input_buf(info, &buff, &lens);
	if (m == -1)
		return (-1);
	if (lens)
	{
		k = j;
		q = buff + j;

		check_chain(info, buff, &k, j, lens);
		while (k < lens)
		{
			if (is_chain(info, buff, &k))
				break;
			k++;
		}
		j = k + 1;
		if (j >= lens)
		{
			j = lens = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buff_q = q;
		return (_strlen(q));
	}
	*buff_q = buff;
	return (m);
}

/**
 * read_buf - will read the buffer
 * @buff: buffer itself
 * @j: buffger size
 * @info: info
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buff, size_t *j)
{
	ssize_t m = 0;

	if (*j)
		return (0);
	m = read(info->readfd, buff, READ_BUF_SIZE);
	if (m >= 0)
		*j = m;
	return (m);
}

/**
 * _getline - will get the next line of input
 * @pntr: the address of the pointer to the buffer
 * @leng: the size of the preallocated pointer buffer
 * @info: info
 * Return: t
 */
int _getline(info_t *info, char **pntr, size_t *leng)
{
	static char buff[READ_BUF_SIZE];
	static size_t j, lens;
	size_t l;
	ssize_t s = 0, t = 0;
	char *q = NULL, *new_q = NULL, *d;

	q = *pntr;
	if (q && leng)
		t = *leng;
	if (j == lens)
		j = lens = 0;

	s = read_buf(info, buff, &lens);
	if (s == -1 || (s == 0 && lens == 0))
		return (-1);

	d = _strchr(buff + j, '\n');
	l = d ? 1 + (unsigned int)(d - buff) : lens;
	new_q = _realloc(q, t, t ? t + l : l + 1);
	if (!new_q)
		return (q ? free(q), -1 : -1);

	if (t)
		_strncat(new_q, buff + j, l - j);
	else
		_strncpy(new_q, buff + j, l - j + 1);

	t += l - j;
	j = l;
	q = new_q;

	if (leng)
		*leng = t;
	*pntr = q;
	return (t);
}
