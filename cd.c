#include "shell.h"
/**
 * change_old_pwd - changes OLDPWD variable
 * @envp: environment
 * @ldbuf: last directory buffer
 * @opwd: OLDPWD buffer
 * Return: NULL
 */
char *change_old_pwd(char *envp[], char ldbuf[], char opwd[])
{
	char *path = "OLDPWD", buffer[1000];
	int i = 0;

	while (envp[i])
	{
		if (_strncmp(envp[i], path, 6) == 0)
		{
			_strcpy(buffer, ldbuf);
			_memset(opwd, 0, 1000);
			_strcpy(opwd, "OLDPWD=");
			_strcat(opwd, buffer);
			envp[i] = opwd;
		}
		i++;
	}

	return (NULL);
}
/**
 * get_old_pwd - gets OLDPWD variable
 * @envp: environment
 * @opwd: OLDPWD buffer
 * Return: copy of OLDPWD
 */
char *get_old_pwd(char *envp[], char opwd[])
{
	int i = 0;
	char *path = "OLDPWD";

	while (envp[i])
	{
		if (_strncmp(envp[i], path, 6) == 0)
		{
			_strcpy(opwd, envp[i]);
			return (opwd);
		}
		i++;
	}
	return (NULL);
}
/**
 * cd_helper - sets PWD variable
 * @cwd: current working directory
 * @pwd: PWD buffer
 * @envp: environment
 */
void cd_helper(char cwd[], char pwd[], char *envp[])
{
	int i = 0;

	getcwd(cwd, 1000);
	_strcat(pwd, cwd);
	while (envp[i])
	{
		if (_strncmp(envp[i], "PWD", 3) == 0)
			envp[i] = pwd;
		i++;
	}
}
/**
 * cd_home - handles cd with no arguments
 * @a: buf struct pointer
 * @pb: path buffer
 */
void cd_home(buf_struct *a, char *pb[])
{
	char cwd[1000], temp[1000], *home_path, home_copy[1000];

	_strcpy(temp, a->ldbuf);
	home_path = get_home_path(a->envp);
	_strcpy(home_copy, home_path);
	_split(home_copy, pb);
	if (chdir(pb[1]) != 0)
		perror("hsh");
	else
	{
		getcwd(a->ldbuf, 1000);
		cd_helper(cwd, a->pwdb, a->envp);
		change_old_pwd(a->envp, temp, a->opwdb);
	}
}
/**
 * cd - changes directory
 * @a: buf struct pointer
 */
void cd(buf_struct *a)
{
	char *path_buf[1000];
	char buffer[1000], cwd[1000], temp[1000], *pwd_split[1000];

	a->ex_stat = 0;
	_memset(a->pwdb, 0, 1000);
	_strcpy(a->pwdb, "PWD=");
	_memset(buffer, 0, 1000);
	_itoa(a->hist, buffer);
	if (a->args[1])
	{
		if (_strcmp(a->args[1], "-") == 0)
		{
			_strcpy(temp, a->ldbuf);
			get_old_pwd(a->envp, a->opwdb);
			_split(a->opwdb, pwd_split);
			if (chdir(pwd_split[1]) != 0)
				chdir(a->ldbuf);
			else
			{
				getcwd(a->ldbuf, 1000);
				cd_helper(cwd, a->pwdb, a->envp);
				change_old_pwd(a->envp, temp, a->opwdb);
				write(STDOUT_FILENO, a->ldbuf, _strlen(a->ldbuf));
				write(STDOUT_FILENO, "\n", 1);
			}
		}
		else
		{
			_strcpy(temp, a->ldbuf);
			if (chdir(a->args[1]) != 0)
				error_cd(a, buffer);
			else
			{
				getcwd(a->ldbuf, 1000);
				cd_helper(cwd, a->pwdb, a->envp);
				change_old_pwd(a->envp, temp, a->opwdb);
			}
		}
	}
	else
		cd_home(a, path_buf);
}
