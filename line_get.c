#include "shell.h"

/**
 * input_buf - function buffer
 * @length: address of the buffer
 * @info: info
 * @buf: buffer
 * Return: bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *length)
{
        size_t len_q = 0;
        ssize_t s = 0;

        if (!*length)
        {
                /*bfree((void **)info->cmd_buf);*/
                free(*buf);
                *buf = NULL;
                signal(SIGINT, sigintHandler);
#if USE_GETLINE
                s = getline(buf, &len_q, stdin);
#else
                s = _getline(info, buf, &len_q);
#endif
                if (s > 0)
                {
                        if ((*buf)[s - 1] == '\n')
                        {
                                (*buf)[s - 1] = '\0';
                                s--;
                        }
                        info->linecount_flag = 1;
                        remove_comments(*buf);
                        build_history_list(info, *buf, info->histcount++);
                        /* if (_strchr(*buf, ';')) command chain? */
                        {
                                *length = s;
                                info->cmd_buf = buf;
                        }
                }
        }
        return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_no: signal num
 * Return: nothing
 */
void sigintHandler(__attribute__((unused))int sig_no)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * read_buf - reads buffer
 * @info: info
 * @a: size
 * @buff: buff
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buff, size_t *a)
{
	ssize_t r = 0;

	if (*a)
		return (0);
	r = read(info->readfd, buff, READ_BUF_SIZE);
	if (r >= 0)
		*a = r;
	return (r);
}

/**
 * _getline - gets the next line of input
 * @info: info
 * @lengt: size of ptr buffer
 * @pt: the address of pointer to buffer
 * Return: s
 */
int _getline(info_t *info, char **pt, size_t *lengt)
{
	size_t n;
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	char *q = NULL, *new_q = NULL, *c;
	ssize_t r = 0, s = 0;

	q = *pt;
	if (q && lengt)
		s = *lengt;
	if (j == len)
		j = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	n = c ? 1 + (unsigned int)(c - buf) : len;
	new_q = _realloc(q, s, s ? s + n : n + 1);
	if (!new_q)
		return (q ? free(q), -1 : -1);

	if (s)
		_strncat(new_q, buf + j, n - j);
	else
		_strncpy(new_q, buf + j, n - j + 1);

	s += n - j;
	j = n;
	q = new_q;

	if (lengt)
		*lengt = s;
	*pt = q;
	return (s);
}

/**
 * get_input - gets line
 * @info: info
 * Return: bytes
 */
ssize_t get_input(info_t *info)
{
	static size_t j, k, length;
	static char *buf;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &length);
	if (r == -1)
		return (-1);
	if (length)
	{
		k = j;
		p = buf + j;

		check_chain(info, buf, &k, j, length);
		while (k < length)
		{
			if (is_chain(info, buf, &k))
				break;
			k++;
		}

		j = k + 1; /* nulled increment ';'' */
		if (j >= length)
		{
			j = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}
