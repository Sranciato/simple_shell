#include "shell.h"

/**
 * pipe_file - handles files piped in
 * @a: buf struct pointer
 */
void pipe_file(buf_struct *a)
{
	char *path_buf[1000], *semi_buf[1000], *path, **test;
	int i, ext;

	_split_newline(a->rbuf, semi_buf);
	for (i = 0; semi_buf[i]; i++)
	{
		_strcpy(a->history[a->hist++], a->rbuf);
		check_comment(a->rbuf);
		if ((check_semiandor(a) == 1))
                        continue;
		test = _split(semi_buf[i], a->args);
		if (test == NULL)
			continue;
		if (check_exit(a) == 1)
                        continue;
		path = get_path(a->envp);
		_strcpy(a->path_copy, path);
		_split(a->path_copy, path_buf);
		find_path(path_buf, a->args, a->dest);
		ext = execute(a, a->dest);
		_memset(a->args, 0, sizeof(a->args));
		_memset(a->dest, 0, 1000);
	}
	exit(ext);
}
