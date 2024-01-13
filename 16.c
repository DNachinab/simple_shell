#include "sshell.h"

/**
 * len_str - returns the length of a string
 * @s: the string
 *
 * Return: the length of string (integer)
 */

int len_str(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * comp_str - compares of two strangs (lexicogarphic).
 * @s1: first string
 * @s2: the second string
 *
 * Return: (-) if s1 < s2, (+) if s1 > s2, 0 if s1 == s2
 */

int comp_str(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * start_hay - checks if starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack, otherwise NULL
 */

char *start_hay(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * concat_str - concatenates two strings
 * @dest: destination buffer
 * @src: source buffer
 *
 * Return: pointer to destination buffer
 */

char *concat_str(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}