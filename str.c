#include "shell.h"

/**
 * _strcpy - copy string
 * @dest: destination string
 * @src: source string
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int count = 0, loop;


	while (src[count] != '\0')
		count++;

	for (loop = 0; loop <= count; loop++)
		dest[loop] = src[loop];
	return (dest);
}
/**
 * _strcat - concatenate two strings
 * @dest: dest string
 * @src: srouce string
 * Return: pointer to dest
 */
char *_strcat(char *dest, char *src)
{
	int loop1 = 0, loop2 = 0;

	while (*(dest + loop1) != '\0')
		loop1++;

	while (*(src + loop2) != '\0')
	{
		*(dest + loop1) = *(src + loop2);
		loop1++;
		loop2++;
	}
	return (dest);
}
/**
 * _strcmp - compare strings
 * @s1: string 1
 * @s2: string 2
 * Return: difference between ascii value
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}
/**
 * _strncmp - compare n bytes of string
 * @s1: string 1
 * @s2: string 2
 * @n: bytes to compare
 * Return: difference between ascii value
 */
int _strncmp(char *s1, char *s2, int n)
{
	while (n > 1)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
		n--;
	}
	return (*s1 - *s2);
}
/**
 * _strlen - gets length of string
 * @s: input string
 * Return: length
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		;
	return (i);
}
