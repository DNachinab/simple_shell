#include "sshell.h"

/**
 **_locmem - sets memory with a fixed byte
 *@m: pointer to memory area
 *@b: byte *m will fill
 *@n: amt of bytes to be filled
 *Return: pointer to the memory area *m
 */

char *_locmem(char *m, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		m[i] = b;
	return (m);
}

/**
 * _ffree - frees a string within strings
 * @pp: string with strings
 */
void _ffree(char **pp)
{
	char **x = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(x);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to prev malloc block
 * @old_size: byte size of prev block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}