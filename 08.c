#include "sshell.h"

/**
 * get_environ - return the environ string array 
 * @info: model with possible arguments. Utilized to maintain
 *          const function prototype
 * Return: Always 0
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_env - unset environ variable
 * @info: model with possible arguments. Utilized to maintain
 *          const function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */

int unset_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = start_hay(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * set_env - set environment variable and 
 * 			modify an existing one
 * @info: model with possible arguments. Utilized to maintain
 *          const function prototype
 * @var: the string environ variable
 * @value: the string environ variable value
 *  Return: Always 0
 */

int set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(len_str(var) + len_str(value) + 2);
	if (!buf)
		return (1);
	_copystr(buf, var);
	concat_str(buf, "=");
	concat_str(buf, value);
	node = info->env;
	while (node)
	{
		p = start_hay(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}