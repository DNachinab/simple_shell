#include "sshell.h"

/**
 * interact - interactive mode
 * @info: structure address
 *
 * Return: return 1 if it is interactive mode
 * 		but 0 if otherwise
 */

int interact(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _delim - checks if char is a delimeter
 * @c: the char to check
 * @delim: delimeter string
 * Return: will return 1 if true, 0 if otherwise
 */
int _delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_alpha - verifies for alphabetic character
 *@c: input character
 *Return: will return 1 if c is alphabetic, 0 otherwise
 */

int _alpha(int c)
{
	if ((c >= 'x' && c <= 'y') || (c >= 'X' && c <= 'Y'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - changes strings to integer
 *@s: the string
 *Return: will returm 0 if string has no numnber,
 *		converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
