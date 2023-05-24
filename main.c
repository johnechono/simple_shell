#include "shell.h"

/**
 * main - strating point
 * @ac: argument count
 * @av: argument vector
 * Return: 0 o/w: 1
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fe = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fe)
		: "r" (fe));

	if (ac == 2)
	{
		fe = open(av[1], O_RDONLY);
		if (fe == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fe;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
