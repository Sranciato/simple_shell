#include "shell.h"

/**
 * pipe_file - handles files piped in
 * @a: buf struct pointer
 */
void pipe_file(buf_struct *a)
{
	char *path_buf[1000], *semi_buf[1000], *path;
	int i, ext;

	_split_newline(a->rbuf, semi_buf);
	for (i = 0; semi_buf[i]; i++)
	{
		a->hist++;
		_split(semi_buf[i], a->args);
		path = get_path(a->envp);
		_strcpy(a->path_copy, path);
		_split(a->path_copy, path_buf);
		if (a->args[0][0] == '/')
		{
			execute(a, a->args[0]);
			_memset(a->args, 0, sizeof(a->args));
			_memset(a->dest, 0, 1000);
			continue;
		}
		find_path(path_buf, a->args, a->dest);
		ext = execute(a, a->dest);
		_memset(a->args, 0, sizeof(a->args));
		_memset(a->dest, 0, 1000);
	}
	exit(ext);
}
