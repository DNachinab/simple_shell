#include "sshell.h"

/**
 * _clearinfo - initializes info_t struct
 * @info: struct address
 */
void _clearinfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * _setinfo - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void _setinfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = splitstr(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _dupstr(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		rep_alias(info);
		rep_vars(info);
	}
}

/**
 * _freeinfo - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void _freeinfo(info_t *info, int all)
{
	_ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		_ffree(info->environ);
			info->environ = NULL;
		_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}