#include "sshell.h"

/**
 **_cpystrn - copies string
 *@dest: destination where the string should be copied to
 *@src: the source
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */

char *_cpystrn(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_catstr - concatenates 2 strings
 *@dest: the first string
 *@src: the second string
 *Return: the string that is concatenated
 */

char *_catstr(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_locchar - locates a character in a string
 *@s: the string to be parsed
 *@c: character
 *Return: (s) a pointer to the memory area s
 */

char *_locchar(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}