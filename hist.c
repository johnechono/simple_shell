#include "shell.h"

/**
 * get_history_file - gets the history file for sure
 * @info: Parameter
 * Return: Allocated string
 */

char *get_history_file(info_t *info)
{
	char *buf, *_dir;

	_dir = _getenv(info, "HOME=");
	if (!_dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(_dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, _dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - It creates a file
 * @info: The parameter
 * Return: 1
 */
int write_history(info_t *info)
{
	ssize_t _fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	_fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (_fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, _fd);
		_putfd('\n', _fd);
	}
	_putfd(BUF_FLUSH, _fd);
	close(_fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 * Return: histcount on success
 */
int read_history(info_t *info)
{
	ssize_t fd, rdlen, fsize = 0;
	int j, last = 0, linecout = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (j = 0; j < fsize; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			build_history_list(info, buf + last, linecout++);
			last = j + 1;
		}
	if (last != j)
		build_history_list(info, buf + last, linecout++);
	free(buf);
	info->histcount = linecout;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to linked list
 * @info: Structure containing potential arguments
 * @buf: buff
 * @linecount: the history linecount
 * Return: 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list
 * @info: Structure containing potential arguments
 * Return: histcount
 */
int renumber_history(info_t *info)
{
	int j = 0;
	list_t *node = info->history;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}

