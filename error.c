#include "shell.h"

/**
 * _error - handles execve errors
 * @a: buf struct pointer
 * @buffer: line number
 */
void _error(buf_struct *a, char buffer[])
{
	write(STDOUT_FILENO, a->argv[0], _strlen(a->argv[0]));
	write(STDOUT_FILENO, ": ", 2);

	write(STDOUT_FILENO, buffer, 4);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, a->args[0], _strlen(a->args[0]));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "not found", 9);
	write(STDOUT_FILENO, "\n", 1);
}
/**
 * error_cd - handles errors for cd
 * @a: buf struct pointer
 * @buffer: line number
 */
void error_cd(buf_struct *a, char buffer[])
{
	a->ex_stat = 2;
	write(STDOUT_FILENO, a->argv[0], _strlen(a->argv[0]));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, buffer, 4);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "cd: can't cd to ", 16);
	write(STDOUT_FILENO, a->args[1], _strlen(a->args[1]));
	write(STDOUT_FILENO, "\n", 1);
}
