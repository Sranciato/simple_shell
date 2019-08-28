#include "shell.h"

/**
 * _atoi - converts string to int
 * @s: input string
 * Return: converted int
 */
int _atoi(char *s)
{
	int loop, digitCount = 0, neg = 1, start = 0, multiple = 1;

	int temp, number = 0;

	for (loop = 0; s[loop] != '\0'; loop++)
	{
		if (s[loop] == '-')
			neg *= -1;
		if (s[loop] >= 48 && s[loop] <= 57)
		{
			digitCount++;
			if (digitCount > 1)
				multiple *= 10;
			if (!(s[loop + 1] >= 48 && s[loop + 1] <= 57))
				break;
		}
	}
	for (start = (loop + 1) - digitCount; start < loop + 1; start++)
	{
		temp = (s[start] - '0') * multiple;
		number += temp;
		multiple /= 10;
	}
	number *= neg;
	return (number);
}
/**
 * _itoa - converts int to string
 * @n: input int
 * @buf: buffer for string
 * Return: length of string
 */
int _itoa(int n, char buf[])
{
	int i = 0, temp, start = 0, len;
	char buffer[1000];

	if (n == 0)
	{
		buf[0] = '0';
		return (1);
	}
	if (n < 0)
	{
		buffer[i] = '-';
		i++;
		n = -n;
	}
	while (n)
	{
		temp = n % 10;

		if (temp > 9)
		{
			buffer[i] = (temp - 10) + 'A';
			i++;
		}
		else if (temp < 10)
		{
			buffer[i] = temp + '0';
			i++;
		}
		n = n / 10;
	}
	i--;
	len = i;
	while (i >= 0)
	{
		buf[start] = buffer[i];
		start++;
		i--;
	}
	return (len);
}
