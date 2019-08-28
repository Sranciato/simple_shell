#include "shell.h"

/**
 * _read - reads line from STDIN
 * @buf: buffer for input
 * Return: pointer to input
 */
char *_read(char *buf)
{
	int rd;

	rd = read(STDIN_FILENO, buf, 1024);
	if (rd == 1 || rd == -1)
		return (NULL);
	else if (rd == 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(EXIT_SUCCESS);
	}
	return (buf);
}
