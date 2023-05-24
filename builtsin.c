#include "shell.h"

/**
 * _myhelp - change process directory
 * @info: containing argument
 * Return: 0
 */
int _myhelp(info_t *info)
{
	char **array_args;

	array_args = info->argv;
	_puts("call help. Function not called \n");
	if (0)
		_puts(*array_args);
	return (0);
}

/**
 * _myexit - exits shell project
 * @info: Used to maintain constant function prototype
 * Return: exits
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int check_exit;

	if (info->argv[1])
	{
		check_exit = _erratoi(info->argv[1]);
		if (check_exit == -1)
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;

	return (-2);
}

/**
 * _mycd - Change the current  process dir
 * @info: maintain constant function
 * Return: 0
 */
int _mycd(info_t *info)
{
	int ret_chdir;
	char *a, *dir, buffer[1024];

	a = getcwd(buffer, 1024);
	if (!a)
		_puts("TODO: >>getcwd msg for failure<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			ret_chdir = /* TODO: what should it be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			ret_chdir = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(a);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		ret_chdir = /* TODO: what should it be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		ret_chdir = chdir(info->argv[1]);
	if (ret_chdir == -1)
	{
		print_error(info, "cannot cd into ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

