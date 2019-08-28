#include "shell.h"

/**
 * sigint_handler - handles SIGINT calls
 * @sig_num: signal number
 */
void sigint_handler(int sig_num)
{
	(void) sig_num;
	signal(SIGINT, sigint_handler);
}
