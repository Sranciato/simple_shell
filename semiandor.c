#include "shell.h"

/**
 * _semi - handles commands with semicolon
 * @sbuf: buffer for tokenized string
 * @a: buf struct pointer
 */
void _semi(char *sbuf[], buf_struct *a)
{
	char *path;
	char dest[1000];
	int i;

	for (i = 0; sbuf[i]; i++)
	{
		_memset(dest, 0, 1000);
		_memset(a->args, 0, sizeof(a->args));
		_split(sbuf[i], a->args);
		if ((check_bltin(a) != 0))
			continue;
		path = get_path(a->envp);
		_strcpy(a->path_copy, path);
		_split(a->path_copy, a->path_buf);

		if (a->args[0][0] == '/')
		{
			execute(a, NULL);
			continue;
		}
		check_comment(sbuf[i]);
		find_path(a->path_buf, a->args, dest);
		execute(a, dest);
	}
}
/**
 * _and - handles commands with &&
 * @sbuf: buffer for tokenized string
 * @a: buf struct pointer
 */
void _and(char *sbuf[], buf_struct *a)
{
	char dest[1000], *path;
	int i, check = 0;

	for (i = 0; sbuf[i]; i++)
	{
		_memset(dest, 0, 1000);
		_memset(a->args, 0, sizeof(a->args));
		_split(sbuf[i], a->args);
		if ((check_bltin(a) != 0))
			continue;
		path = get_path(a->envp);
		_strcpy(a->path_copy, path);
		_split(a->path_copy, a->path_buf);

		if (a->args[0][0] == '/')
		{
			check = execute(a, a->args[0]);
			if (check != 0)
				break;
			continue;
		}
		find_path(a->path_buf, a->args, dest);
		check = execute(a, dest);
		if (check != 0)
			break;
	}
}
/**
 * _or - handles commands with ||
 * @sbuf: buffer for tokenized string
 * @a: buf struct pointer
 */
void _or(char *sbuf[], buf_struct *a)
{
	char dest[1000], *path;
	int i, or;

	for (i = 0; sbuf[i]; i++)
	{
		_memset(dest, 0, 1000);
		_memset(a->args, 0, sizeof(a->args));
		_split(sbuf[i], a->args);
		if ((check_bltin(a) != 0))
			continue;
		path = get_path(a->envp);
		_strcpy(a->path_copy, path);
		_split(a->path_copy, a->path_buf);
		if (a->args[0][0] == '/')
		{
			or = execute(a, a->args[0]);
			if (or == 0)
				break;
			continue;
		}
		find_path(a->path_buf, a->args, dest);
		or = execute(a, dest);
		if (or == 0)
			break;
	}
}
/**
 * _split_semiandor - splits lines with ; && ||
 * @s: input string
 * @buf: buffer for tokenized string
 * Return: buffer with tokenized string
 */
char **_split_semiandor(char *s, char *buf[])
{
	char delim[] = ";&|";
	char *token;
	int i = 0;

	token = strtok(s, delim);

	while (token != NULL)
	{
		buf[i] = token;
		token = strtok(NULL, delim);
		i++;
	}

	if (buf == NULL)
		return (NULL);

	return (buf);
}
/**
 * check_semiandor - checks string for ; && ||
 * @a: buf struct pointer
 * Return: 1 if found, 0 otherwise
 */
int check_semiandor(buf_struct *a)
{
	int i = 0;
	char *semi_buf[1000];

	_memset(semi_buf, 0, sizeof(semi_buf));
	while (a->rbuf[i])
	{
		if (a->rbuf[i] == ';')
		{
			if (i == 0 || a->rbuf[i + 1] == '\0')
				return (1);
			_split_semiandor(a->rbuf, semi_buf);
			_semi(semi_buf, a);
			return (1);
		}
		else if (a->rbuf[i] == '&' && a->rbuf[i + 1] == '&')
		{
			if (i == 0 || a->rbuf[i + 1] == '\0')
				return (1);
			_split_semiandor(a->rbuf, semi_buf);
			_and(semi_buf, a);
			return (1);
		}
		else if (a->rbuf[i] == '|' && a->rbuf[i + 1] == '|')
		{
			if (i == 0 || a->rbuf[i + 1] == '\0')
				return (1);
			_split_semiandor(a->rbuf, semi_buf);
			_or(semi_buf, a);
			return (1);
		}
		i++;
	}
	return (0);
}
