#include "shell.h"
/**
 * make_struct_a - creates a struct of buffers
 * @envp: envp
 * @argv: argv
 * Return: buf struct pointer
 */
buf_struct *make_struct_a(char *envp[], char *argv[])
{
	static buf_struct a;

	a.envp = envp;
	a.argv = argv;
	a.hist = 0;
	a.ex_stat = 0;
	_memset(a.path_buf, 0, sizeof(a.path_buf));
	_memset(a.history, 0, sizeof(a.history));

	return (&a);
}
/**
 * main_loop - main loop of program
 * @a: struct of buffers
 */
void main_loop(buf_struct *a)
{
	char **test, *path;
	int ext;

	_memset(a->ldbuf, 0, 1000);
	getcwd(a->ldbuf, 1000);
	while (1)
	{
		_memset(a->rbuf, 0, 1024);
		_memset(a->args, 0, sizeof(a->args));
		_memset(a->dest, 0, 1000);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		if (((_read(a->rbuf)) == NULL))
			continue;
		if (isatty(STDIN_FILENO) == 0)
			pipe_file(a);
		_strcpy(a->history[a->hist++], a->rbuf);
		check_comment(a->rbuf);
		if ((check_semiandor(a) == 1))
			continue;
		test = _split(a->rbuf, a->args);
		if (test == NULL)
			continue;
		ext = check_exit(a);
		if (ext == 1)
			continue;
		if ((check_bltin(a) != 0))
			continue;
		path = get_path(a->envp);
		_strcpy(a->path_copy, path);
		_split(a->path_copy, a->path_buf);
		find_path(a->path_buf, a->args, a->dest);
		execute(a, a->dest);
	}
}
/**
 * main - entry point
 * @argc: number of arguments
 * @argv: array of arguments
 * @envp: enviornment
 * Return: always 0
 */
int main(int argc, char *argv[], char *envp[])
{
	buf_struct *a;

	a = make_struct_a(envp, argv);

	signal(SIGINT, sigint_handler);
	if (argc == 2)
		file_input(a);
	main_loop(a);

	return (0);
}
