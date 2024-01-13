#include "sshell.h"

/**
 * **splitstr - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings if successful,
 * 			 otherwise NULL
 */

char **splitstr(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **x;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_delim(str[i], d) && (_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	x = malloc((1 + numwords) * sizeof(char *));
	if (!x)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (_delim(str[i], d))
			i++;
		k = 0;
		while (!_delim(str[i + k], d) && str[i + k])
			k++;
		x[j] = malloc((k + 1) * sizeof(char));
		if (!x[j])
		{
			for (k = 0; k < j; k++)
				free(x[k]);
			free(x);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			x[j][m] = str[i++];
		x[j][m] = 0;
	}
	x[j] = NULL;
	return (x);
}

/**
 * **splitstr2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings if successful,
 * 			 otherwise NULL
 */

char **splitstr2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **x;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	x = malloc((1 + numwords) * sizeof(char *));
	if (!x)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		x[j] = malloc((k + 1) * sizeof(char));
		if (!x[j])
		{
			for (k = 0; k < j; k++)
				free(x[k]);
			free(x);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			x[j][m] = str[i++];
		x[j][m] = 0;
	}
	x[j] = NULL;
	return (x);
}