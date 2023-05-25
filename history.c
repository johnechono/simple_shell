#include "shell.h"

/**
 * renumber_history - will renumber the history
 * @info: history info
 * Return: new count
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}

/**
 * get_history_file - will get the history
 * @info: struct parameter
 * Return: the allocated string
 */
char *get_history_file(info_t *info)
{
	char *dir, *buff;

	dir = _getenv(info, "HOME=");
	if (!dir)
	{
		return (NULL);
	}
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
	{
		return (NULL);
	}
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - will create or append the file
 * @info: struct parameter
 * Return: 1 o/w 0
 */
int write_history(info_t *info)
{
	char *file_name = get_history_file(info);
	list_t *node = NULL;
	ssize_t fd;

	if (!file_name)
	{
		return (-1);
	}

	fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (fd == -1)
	{
		return (-1);
	}
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - will read file history
 * @info: struct parameter
 * Return: history count
 */
int read_history(info_t *info)
{
	struct stat st;
	int last, j = 0, line_count = 0;
	ssize_t fd, rd_len, f_size = 0;
	char *buff = NULL, *file_name = get_history_file(info);

	if (!file_name)
		return (0);
	fd = open(file_name, O_RDONLY);
	free(file_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buff = malloc(sizeof(char) * (f_size + 1));
	if (!buff)
		return (0);
	rd_len = read(fd, buff, f_size);
	buff[f_size] = 0;
	if (rd_len <= 0)
		return (free(buff), 0);
	close(fd);
	for (j = 0; j < f_size; j++)
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			build_history_list(info, buff + last, line_count++);
			last = j + 1;
		}
	if (last != j)
		build_history_list(info, buff + last, line_count++);
	free(buff);
	info->histcount = line_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - history linked list entry
 * @info: info
 * @buff: the buffer
 * @line_count: linecount history
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buff, int line_count)
{
	list_t *nodal = NULL;

	if (info->history)
		nodal = info->history;
	add_node_end(&nodal, buff, line_count);

	if (!info->history)
	{
		info->history = nodal;
	}
	return (0);
}

