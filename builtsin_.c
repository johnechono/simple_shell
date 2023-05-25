#include "shell.h"

/**
 * _myhelp - change process directory
 * @info: containing argument
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("pls call function correctly \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

/**
 * _myexit - exits the shell
 * @info:  maintaining the function
 * Return: status
 */
int _myexit(info_t *info)
{
	int exit_check;

	if (info->argv[1])
	{
		exit_check = _erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Invalid num: ");
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
 * _mycd - change the current process directory
 * @info: maintaining the function
 *  Return: 0
 */
int _mycd(info_t *info)
{
	int chdir_retn;
	char *a, *dir, buffer[1024];

	a = getcwd(buffer, 1024);
	if (!a)
		_puts("note: >>display getcwd message<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_retn = /* note: what will happen here */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_retn = chdir(dir);
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
		chdir_retn = /* note: what will happen here? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_retn = chdir(info->argv[1]);
	if (chdir_retn == -1)
	{
		print_error(info, "won't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
