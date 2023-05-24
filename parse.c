#include "shell.h"

/**
 * is_cmd - checks if the file is a cmd
 * @path: file path
 * @info: struct info
 * Return: 1 O/W 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat su;

	(void)info;
	if (!path || stat(path, &su))
		return (0);

	if (su.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * find_path - finds this cmd in the PATH string
 * @cmd: executable
 * @path_str: PATH of the string
 * @info: strut info
 * Return: complete path or NULL
 */
char *find_path(info_t *info, char *path_str, char *cmd)
{
	int j = 0, pos_curr = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[j] || path_str[j] == ':')
		{
			path = dup_chars(path_str, pos_curr, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!path_str[j])
				break;
			pos_curr = j;
		}
		j++;
	}
	return (NULL);
}

/**
 * dup_chars - WILL duplicate the characters
 * @stp: stop
 * @path_str: string of the PATH
 * @strt: start
 * Return: pointer
 */
char *dup_chars(char *path_str, int strt, int stp)
{
	static char buf[1024];
	int j = 0, l = 0;

	for (l = 0, j = strt; j < stp; j++)
		if (path_str[j] != ':')
		{
			buf[l++] = path_str[j];
		}
	buf[l] = 0;
	return (buf);
}
