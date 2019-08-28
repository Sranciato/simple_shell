#include "shell.h"

/**
 * file_input - takes file as input
 * @a: buf struct pointer
 */
void file_input(buf_struct *a)
{
	int fd, rd, i, hist  = 0;
	char *semi_buf[1000], *path, *path_buf[1000];

	fd = open(a->argv[0], O_RDONLY);
	if (fd == -1)
		perror("hsh");

	rd = read(fd, a->rbuf, 1024);
	if (rd == -1)
		perror("hsh");
	close(rd);
	_split_newline(a->rbuf, semi_buf);
	for (i = 0; semi_buf[i]; i++)
	{
		hist++;
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
		execute(a, a->dest);
		_memset(a->args, 0, sizeof(a->args));
		_memset(a->dest, 0, 1000);
	}
	exit(0);
}
