#include "sshell.h"

/**
 * _free - freeing pointers
 * @ptr: the pointer address to be freed
 * Return: if freed return, alternatively return 0.
 */

int _free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
