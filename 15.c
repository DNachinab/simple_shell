#include "sshell.h"

/**
 * _iscmd - checks if a file is an exe command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */

int _iscmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * reprint_chars - replicate characters
 * @pathstr: the PATH string
 * @start: start index
 * @stop: stop index
 *
 * Return: pointer to new buffer
 */

char *reprint_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - finds coomand in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the command
 *
 * Return: reurn full path of command if found,
 * 			otherwise NULL
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((len_str(cmd) > 2) && start_hay(cmd, "./"))
	{
		if (_iscmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = reprint_chars(pathstr, curr_pos, i);
			if (!*path)
				concat_str(path, cmd);
			else
			{
				concat_str(path, "/");
				concat_str(path, cmd);
			}
			if (_iscmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}