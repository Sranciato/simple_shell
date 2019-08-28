#include "shell.h"

/**
 * check_comment - checks for comments
 * @rbuffer: input string
 */
void check_comment(char rbuffer[])
{
	int i = 0, com = 0;
	char comment[1000];
	char delim[] = "#";

	(void) comment;
	while (rbuffer[i])
	{
		if (rbuffer[i] == '#')
			com = 1;
		i++;
	}

	if (com == 1)
		strtok(rbuffer, delim);
}
