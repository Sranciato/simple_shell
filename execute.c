#include "shell.h"

char *set_path(buf_struct *a, char path_buf[])
{
	getcwd(path_buf, 1000);
	_strcat(path_buf, "/");
	_strcat(path_buf, a->args[0]);
	return (path_buf);
}
/**
 * execute - execute command
 * @a: buf struct pointer
 * @path: path of command
 * Return: exit status of command
 */
int execute(buf_struct *a, char *path)
{
	pid_t pid;
	int status = 0;
	char buffer[1000], path_buf[1000];

	pid = fork();
	_memset(buffer, 0, 1000);
	_itoa(a->hist, buffer);
	if (path[0] == 0)
		path = set_path(a, path_buf);
	if (pid == 0)
	{
		if (a->args[0][0] == '/')
		{
			if (execve(a->args[0], a->args, a->envp) == -1)
			{
				_error(a, buffer);
				_exit(errno);
			}
		}
		if (execve(path, a->args, a->envp) == -1)
		{
			_error(a, buffer);
			_exit(errno);
		}
	}
	else if (pid < 0)
	{
		perror("exe");
		_exit(0);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	a->ex_stat = WEXITSTATUS(status);
	if (a->ex_stat == 13)
		a->ex_stat = 127;
	return (WEXITSTATUS(status));
}
