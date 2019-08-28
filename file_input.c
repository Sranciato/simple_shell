#include "shell.h"

/**
 * file_input - takes file as input
 * @a: buf struct pointer
 */
void file_input(buf_struct *a)
{
	int fd, rd, i, ext = 0;
	char *semi_buf[1000], *path;

	fd = open(a->argv[1], O_RDONLY);
	if (fd == -1)
		perror("hsh");

	rd = read(fd, a->rbuf, 1024);
	if (rd == -1)
		perror("hsh");
	close(rd);
	_split_newline(a->rbuf, semi_buf);
	for (i = 0; semi_buf[i]; i++)
	{
		_memset(a->args, 0, sizeof(a->args));
		_memset(a->dest, 0, 1000);

		a->hist++;
		_split(semi_buf[i], a->args);
		check_comment(a->rbuf);
		if ((check_semiandor(a) == 1))
			continue;
		if ((check_bltin(a) != 0))
			continue;
		path = get_path(a->envp);
		_strcpy(a->path_copy, path);
		_split(a->path_copy, a->path_buf);
		find_path(a->path_buf, a->args, a->dest);
		ext = execute(a, a->dest);
	}
	exit(ext);
}
