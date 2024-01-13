#include "sshell.h"

/**
 * length_l - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t length_l(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - array of strings of the list to string
 * @head: pointer to first node
 *
 * Return: array of strings
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = length_l(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(len_str(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _copystr(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_inputstr(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_inputstr(h->str ? h->str : "(nil)");
		_inputstr("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_start_hay - returns node with prefixes
 * @node: pointer to list head
 * @prefix: string to match
 * @c: character after prefix to comp
 *
 * Return: match node or null
 */

list_t *node_start_hay(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = start_hay(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - retrieves the index node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}