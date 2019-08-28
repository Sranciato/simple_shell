#include "shell.h"

/**
 * get_path - gets path from envp
 * @envp: environment
 * Return: pointer to path
 */
char *get_path(char *envp[])
{
	char *path = "PATH";
	int i = 0;

	while (envp[i])
	{
		if (_strncmp(envp[i], path, 4) == 0)
		{
			return (envp[i]);
		}
		i++;
	}
	return (NULL);
}
/**
 * get_home_path - get the home path
 * @envp: environment
 * Return: pointer to home path
 */
char *get_home_path(char *envp[])
{
	char *path = "HOME";
	int i = 0;

	while (envp[i])
	{
		if (_strncmp(envp[i], path, 4) == 0)
			return (envp[i]);
		i++;
	}

	return (NULL);
}
/**
 * find_path - checks if file is in path
 * @path_buf: buffer for path
 * @args: tokenized input
 * @dest: path for execve
 * Return: path for execve
 */
char *find_path(char *path_buf[], char **args, char dest[])
{
	int i = 0;
	DIR *dir = NULL;
	struct dirent *dp;
	int cmp;
	char *temp = NULL;

	for (i = 1; path_buf[i]; i++)
	{
		dir = opendir(path_buf[i]);
		if (dir == NULL)
			return (NULL);
		temp = path_buf[i];
		while ((dp = readdir(dir)) != NULL)
		{
			cmp = _strcmp(dp->d_name, args[0]);
			if (cmp == 0)
			{
				_memset(dest, 0, 1000);
				_strcpy(dest, temp);
				_strcat(dest, "/");
				_strcat(dest, args[0]);
				closedir(dir);
				return (dest);
			}
		}
		closedir(dir);
	}
	return (NULL);
}
