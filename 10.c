#include "sshell.h"

/**
 * input_buf - inputs buffers commands chain
 * @info: parameter struct
 * @buf: buffer address
 * @len: len var address
 * Return: bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t x = 0;
	size_t len_p = 0;

	/* if nothing left in the buffer, fill it */
	if (!*len)
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, signal_handler);
#if USE_GETLINE
		x = getline(buf, &len_p, stdin);
#else
		x = _getline(info, buf, &len_p);
#endif
		if (x > 0)
		{
			if ((*buf)[x - 1] == '\n')
			{
				(*buf)[x - 1] = '\0';
				x--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_locchar(*buf, ';')) is this a command chain? */
			{
				*len = x;
				info->cmd_buf = buf;
			}
		}
	}
	return (x);
}

/**
 * _getinput - gets a line without the newline
 * @info: parameter struct
 * Return: length of current command,
 * 			or buffer from _getline()
 */

ssize_t _getinput(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t x = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	x = input_buf(info, &buf, &len);
	if (x == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i; 
		p = buf + i; /* get pointer for return */

		ch_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0; 
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pointer to current command position from back*/
		return (len_str(p));
	}

	*buf_p = buf; /* otherwise a chain, buffer from _getline() from back */
	return (x);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * Return: x
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t x = 0;

	if (*i)
		return (0);
	x = read(info->readfd, buf, READ_BUF_SIZE);
	if (x >= 0)
		*i = x;
	return (x);
}

/**
 * _getline - gets line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: y
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t x = 0, y = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		y = *length;
	if (i == len)
		i = len = 0;

	x = read_buf(info, buf, &len);
	if (x == -1 || (x == 0 && len == 0))
		return (-1);

	c = _locchar(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, y, y ? y + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (y)
		_catstr(new_p, buf + i, k - i);
	else
		_cpystrn(new_p, buf + i, k - i + 1);

	y += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = y;
	*ptr = p;
	return (y);
}

/**
 * signal_handler - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */

void signal_handler(__attribute__((unused))int sig_num)
{
	_inputstr("\n");
	_inputstr("$ ");
	_putchar(BUF_FLUSH);
}