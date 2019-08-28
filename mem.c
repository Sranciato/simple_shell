#include "shell.h"


/**
 * _memcpy - copies memory
 * @dest: destination
 * @src: srouce
 * @n: length
 * Return: pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int loop = 0;

	while (loop < n)
	{
		dest[loop] = src[loop];
		loop++;
	}
	return (dest);
}
/**
 * _memset - set memory
 * @s: pointer to memory
 * @c: bytes to fill with
 * @len: length of memory
 * Return: pointer to set memory
 */
void *_memset(void *s, char c, unsigned int len)
{
	char *temp = s;

	while (len > 0)
	{
		*temp = c;
		temp++;
		len--;
	}
	return (temp);
}
