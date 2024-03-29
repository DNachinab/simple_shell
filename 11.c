#include "sshell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (len_str(dir) + len_str(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_copystr(buf, dir);
	concat_str(buf, "/");
	concat_str(buf, HIST_FILE);
	return (buf);
}

/**
 * _writehist - creates a file, or edit existing file
 * @info: the parameter struct
 *
 * Return: return 1 if successful, otherwise -1
 */

int _writehist(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		putfd_str(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _readhist - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, otherwise 0
 */

int _readhist(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
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
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	_renumhistory(info);
	return (info->histcount);
}

/**
 * build_history_list - adds unto history linked-list
 * @info: model with possible arguments. Utilized to maintain
 *          const function prototype
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
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
 * _renumhistory - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */

int _renumhistory(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}