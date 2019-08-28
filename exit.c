#include "shell.h"

/**
 * exit_error - handles error messages for exit
 * @a: buf struct pointer
 * @buffer: line number
 */
void exit_error(buf_struct *a, char buffer[])
{
	write(STDOUT_FILENO, a->argv[0], _strlen(a->argv[0]));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, buffer, 4);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, a->args[0], _strlen(a->args[0]));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "Illegal number", 15);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, a->args[1], _strlen(a->args[1]));
	write(STDOUT_FILENO, "\n", 1);
}
/**
 * check_exit - check for exit call
 * @a: buf struct pointer
 * Return: 1 if error exiting, 0 if not found
 */
int check_exit(buf_struct *a)
{
	char *ex = "exit";
	int exit_code, check = 0;
	char buffer[1000];

	_memset(buffer, 0, 1000);
	_itoa(a->hist, buffer);

	if ((_strncmp(a->args[0], ex, 4)) == 0)
		check = 1;

	if (check == 1)
	{
		if (a->args[1])
		{
			exit_code = _atoi(a->args[1]);
			if (exit_code >= 0 && exit_code <= 2147483647)
				exit(exit_code);
			else
			{
				exit_error(a, buffer);
				return (1);
			}
		}
		else
			exit(a->ex_stat);
	}
	return (0);
}
