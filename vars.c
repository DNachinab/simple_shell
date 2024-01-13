#include "sshell.h"

/**
 * is_chain - verify if the buffer's current character is a chain delimeter
 * @info: the parameter struct
 * @buf: the buffer
 * @p: address of buffer
 *
 * Return: if chain delimeter return 1, otherwise return 0
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * ch_chain - verifies the most recent state of chaining
 * @info: the parameter struct
 * @buf: the buffer
 * @p: address of buffer
 * @i: starting position in buffer
 * @len: length of buffer
 *
 * Return: Void
 */

void ch_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * rep_alias - replaces aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: if replaced return 1, if otherwise return 0.
 */

int rep_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_start_hay(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _locchar(node->str, '=');
		if (!p)
			return (0);
		p = _dupstr(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * rep_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: if replaced return 1, if otherwise return 0.
 */

int rep_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!comp_str(info->argv[i], "$?"))
		{
			rep_str(&(info->argv[i]),
				_dupstr(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!comp_str(info->argv[i], "$$"))
		{
			rep_str(&(info->argv[i]),
				_dupstr(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_start_hay(info->env, &info->argv[i][1], '=');
		if (node)
		{
			rep_str(&(info->argv[i]),
				_dupstr(_locchar(node->str, '=') + 1));
			continue;
		}
		rep_str(&info->argv[i], _dupstr(""));

	}
	return (0);
}

/**
 * rep_str - replaces string
 * @old: old string address
 * @new: new string
 *
 * Return: if replaced return 1, if otherwise return 0.
 */

int rep_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}