#include "shell.h"

/**
 * find_path - finds cmd in the PATH
 * @info: info
 * @pathstr: string path
 * @cmd: cmd
 * Return: full path or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int a = 0, pos_curr = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = dup_chars(pathstr, pos_curr, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[a])
				break;
			pos_curr = a;
		}
		a++;
	}
	return (NULL);
}

/**
 * is_cmd - file is executable
 * @info: info
 * @path: path
 * Return: 1 otherwise 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat sts;

	(void)info;
	if (!path || stat(path, &sts))
		return (0);

	if (sts.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @stp: stop index
 * @pathstr: string path
 * @strt: start index
 * Return: the pointer to buffer
 */
char *dup_chars(char *pathstr, int strt, int stp)
{
	static char buf[1024];
	int a = 0, l = 0;

	for (l = 0, a = strt; a < stp; a++)
		if (pathstr[a] != ':')
			buf[l++] = pathstr[a];
	buf[l] = 0;
	return (buf);
}

