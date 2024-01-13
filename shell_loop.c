#include "sshell.h"

/**
 * hsh - main shell
 * @info: info struct and parameter
 * @av: the argument vector from main()
 * Return: if successful return 0,
 * 			but if error return 1, or error code
 */

int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		_clearinfo(info);
		if (interact(info))
			_inputstr("$ ");
		in_char(BUF_FLUSH);
		r = _getinput(info);
		if (r != -1)
		{
			_setinfo(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interact(info))
			_putchar('\n');
		_freeinfo(info, 0);
	}
	_writehist(info);
	_freeinfo(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: info struct and parameter
 * Return: if builtin not found return -1,
 *			if successfully return 0,
 *			if builtin found but unsuccessful return 1,
 *			else if builtin signals exit() return 2
 */

int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintab[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", myset_env},
		{"unsetenv", myunset_env},
		{"cd", my_ch},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintab[i].type; i++)
		if (comp_str(info->argv[0], builtintab[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintab[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: info struct and parameter
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interact(info) || get_env(info, "PATH=")
			|| info->argv[0][0] == '/') && _iscmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_printerror(info, "NOT FOUND!\n");
		}
	}
}

/**
 * fork_cmd - forks executable thread to run cmd
 * @info: info struct and parameter
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			_freeinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_printerror(info, "Unauthorized Permission\n");
		}
	}
}