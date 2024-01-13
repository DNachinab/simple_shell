#include "sshell.h"

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: return 0 if successful, but if there is
 * 			error, return 1.
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				in_str(av[0]);
				in_str(": 0: Cannot open ");
				in_str(av[1]);
				in_char('\n');
				in_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	_renumhistory(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}