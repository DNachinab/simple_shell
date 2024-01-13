#include "sshell.h"

/**
 * my_env - prints the current environ
 * @info: model with possible arguments. Utilized to maintain
 *          const function prototype
 * Return: 0
 */

int my_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_env - gets environ variable value
 * @info: model with possible arguments. Utilized to maintain
 *          const function prototype
 * @name: environ variable name
 * Return: return the variable value
 */

char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = start_hay(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * myset_env - set environment variable and 
 * 			modify an existing one
 * @info: model with possible arguments. Utilized to maintain
 *          const function prototype
 *  Return: 0
 */

int myset_env(info_t *info)
{
	if (info->argc != 3)
	{
		in_str("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * myunset_env - unset environ variable
 * @info: model with possible arguments. Utilized to maintain
 *          const function prototype
 *  Return: 0
 */

int myunset_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		in_str("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unset_env(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates environ list
 * @info: model with possible arguments. Utilized to maintain
 *          const function prototype
 * Return: 0
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}