#include "shell.h"

/**
 * check_bltin - checks for builtin commands
 * @a: buf struct pointer
 * Return: 1 if found, 0 otherwise
 */
int check_bltin(buf_struct *a)
{
	if (_strcmp(a->args[0], "history") == 0)
	{
		print_history(a->history, a->hist);
		return (1);
	}
	if (_strcmp(a->args[0], "cd") == 0)
	{
		cd(a);
		return (1);
	}
	if (_strcmp(a->args[0], "env") == 0)
	{
		env(a->envp);
		return (1);
	}
	return (0);
}
/**
 * env - prints environment
 * @envp: envp
 */
void env(char *envp[])
{
	int i, j;

	for (i = 0; envp[i]; i++)
	{
		for (j = 0; envp[i][j]; j++)
			;
		write(STDOUT_FILENO, envp[i], j);
		write(STDOUT_FILENO, "\n", 1);
		fflush(stdout);
	}
}
/**
 * print_history - prints history
 * @history: buffer with history
 * @hist: line number
 */
void print_history(char history[][100], int hist)
{
	int i = 0, len;
	char buffer[1000];

	while (i < hist)
	{
		_memset(buffer, 0, 1000);
		if (i == 0)
		{
			write(STDOUT_FILENO, "    ", 4);
			write(STDOUT_FILENO, "0", 1);
		}
		else if (i < 10)
		{
			len = _itoa(i, buffer);
			if (len < 4)
			{
				while (len++ < 4)
					write(STDOUT_FILENO, " ", 1);
			}
			write(STDOUT_FILENO, buffer, 4);
		}
		else if (i > 9)
		{
			len = _itoa(i, buffer);
			if (len < 4)
			{
				while (len++ < 4)
					write(STDOUT_FILENO, " ", 1);
			}
			write(STDOUT_FILENO, buffer, 4);
		}
		write(STDOUT_FILENO, "  ", 2);
		write(STDOUT_FILENO, history[i], sizeof(history[i]));
		i++;
	}
}
