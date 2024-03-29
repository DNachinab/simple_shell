#include "sshell.h"

/**
 * err_atoi - string to an integer
 * @s: the string
 * Return: if no numbers in string it will return 0,
 * 		alternatively will return -1 on error
 */

int err_atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * _printerror - prints an error message
 * @info: info struct and parameter
 * @estr: string with specific error type
 * Return: if no numbers in string it will return 0,
 * 		alternatively will return -1 on error
 */

void _printerror(info_t *info, char *estr)
{
	in_str(info->fname);
	in_str(": ");
	_printd(info->line_count, STDERR_FILENO);
	in_str(": ");
	in_str(info->argv[0]);
	in_str(": ");
	in_str(estr);
}

/**
 * _printd - function prints a decimal or number
 * @input: the input
 * @fd: the filedescriptor
 * Return: the number of char printed
 */

int _printd(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = in_char;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of atoi
 * @num: number
 * @base: base
 * @flags: the flags argument
 * Return: string
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: string address to be modified
 * Return: Always 0;
 */

void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}