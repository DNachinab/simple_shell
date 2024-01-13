#include "sshell.h"

/**
 * my_history - displays the history list
 * @info: model with possible arguments. Utilized to maintain
 *          const function prototype
 *  Return: Always 0
 */

int my_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: alias of the string
 * Return: if successful return 0, 
 * 			and return 1 on error
 */

int unset_alias(info_t *info, char *str)
{
	char *a, c;
	int ret;

	a = _locchar(str, '=');
	if (!a)
		return (1);
	c = *a;
	*a = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_start_hay(info->alias, str, -1)));
	*a = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: if successful return 0, 
 * 			and return 1 on error
 */

int set_alias(info_t *info, char *str)
{
	char *a;

	a = _locchar(str, '=');
	if (!a)
		return (1);
	if (!*++a)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _printalias - prints an alias string
 * @node: the alias node
 * Return: if successful return 0, 
 * 			and return 1 on error
 */

int _printalias(list_t *node)
{
	char *a = NULL, *b = NULL;

	if (node)
	{
		a = _locchar(node->str, '=');
		for (b = node->str; b <= a; b++)
			_putchar(*b);
		_putchar('\'');
		_inputstr(a + 1);
		_inputstr("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics the alias builtin
 * @info: model with possible arguments. Utilized to maintain
 *          const function prototype
 *  Return: 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *a = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_printalias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		a = _locchar(info->argv[i], '=');
		if (a)
			set_alias(info, info->argv[i]);
		else
			_printalias(node_start_hay(info->alias, info->argv[i], '='));
	}

	return (0);
}