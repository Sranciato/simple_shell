#include "shell.h"

/**
 * _split - splits line into tokens
 * @s: input string
 * @buf: buffer for tokens
 * Return: tokenized string
 */
char **_split(char *s, char *buf[])
{
	char delim[] = " \t\r\n\v\f:=";
	char *token;
	int i = 0;

	token = strtok(s, delim);

	while (token != NULL)
	{
		buf[i] = token;
		token = strtok(NULL, delim);
		i++;
	}
	if (buf[0] == NULL)
		return (NULL);
	return (buf);
}
/**
 * _split_newline - splits at newline
 * @s: input string
 * @buf: buffer for tokenized string
 * Return: tokenized string
 */
char **_split_newline(char *s, char *buf[])
{
	char delim[] = "\n";
	char *token;
	int i = 0;

	token = strtok(s, delim);

	while (token != NULL)
	{
		buf[i] = token;
		token = strtok(NULL, delim);
		i++;
	}

	return (buf);
}
