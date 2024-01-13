#include "sshell.h"

/**
 * my_exit - to exit shell
 * @info: model with possible arguments. Utilized to maintain
 *          const function prototype
 *  Return: exit status (0) if info.argv[0] != "exit"
 */

int my_exit(info_t *info)
{
	int exitck;

	if (info->argv[1])
	{
		exitck = err_atoi(info->argv[1]);
		if (exitck == -1)
		{
			info->status = 2;
			_printerror(info, "Unrecognized input: ");
			in_str(info->argv[1]);
			in_char('\n');
			return (1);
		}
		info->err_num = err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * my_ch - alters current directory
 * @info: model with possible arguments. Utilized to maintain
 *          const function prototype
 *  Return: Always 0
 */

int my_ch(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_inputstr("TODO: >>getcwd failure message here<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_ret = 
				chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (comp_str(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_inputstr(s);
			_putchar('\n');
			return (1);
		}
		_inputstr(get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		_printerror(info, "cannot cd into ");
		in_str(info->argv[1]), in_char('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - alters current directory (help)
 * @info: model with possible arguments. Utilized to maintain
 *          const function prototype
 *  Return: Always 0
 */

int my_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_inputstr("Function not yet implemented! Help call!! \n");
	if (0)
		_inputstr(*arg_array); 
	return (0);
}