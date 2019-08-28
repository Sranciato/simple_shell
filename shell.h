#ifndef SHELL_H
#define SHELL_H

#include <sys/stat.h>
#include <sys/types.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>

/**
 * struct buf_struct - Struct for buffers used throughout files.
 * @envp: Environmental list.
 * @path_buf: Buffer for path.
 * @argv: First argument for running shell.
 * @hist: Line number.
 * @history: Buffer for line history.
 * @ex_stat: Exit status.
 * @rbuf: Buffer for line read.
 * @dest: Buffer for _strcpy.
 * @path_copy: Buffer for copying path.
 * @pwdb: Buffer for working directory in path.
 * @opwdb: Buffer for old working directory in path.
 * @args: Buffer for argument list.
 * @ldbuf: Buffer for last directory.
 *
 * Description: - Buffers used globally throughout files..
 */
typedef struct buf_struct
{
	char **envp;
	char *path_buf[1000];
	char **argv;
	int hist;
	char history[100][100];
	int ex_stat;

	char rbuf[1024];
	char dest[1000];
	char path_copy[1000];
	char pwdb[1000];
	char opwdb[1000];
	char *args[1000];
	char ldbuf[1000];
} buf_struct;

void main_loop(buf_struct *a);
buf_struct *make_struct_a(char *envp[], char *argv[]);
void file_input(buf_struct *a);
void pipe_file(buf_struct *a);
int check_semiandor(buf_struct *a);
char **_split_semiandor(char *s, char *buf[]);
void _or(char *sbuf[], buf_struct *a);
void _and(char *sbuf[], buf_struct *a);
void _semi(char *sbuf[], buf_struct *a);
char *get_path(char *envp[]);
int check_bltin(buf_struct *a);
void env(char *envp[]);
void cd(buf_struct *a);
void cd_home(buf_struct *a, char *pb[]);
void cd_helper(char cwd[], char pwd[], char *envp[]);
char *get_old_pwd(char *envp[], char opwd[]);
char *change_old_pwd(char *envp[], char ldbuf[], char opwd[]);
void print_history(char history[][100], int hist);
void check_comment(char rbuffer[]);
void sigint_handler(int sig_num);
char *_read(char *buf);
int check_exit(buf_struct *a);
void exit_error(buf_struct *a, char buffer[]);
char **_split_newline(char *s, char *buf[]);
char **_split(char *s, char *buf[]);
char *find_path(char *path_buf[], char **args, char dest[]);
char *get_home_path(char *envp[]);
int _strncmp(char *s1, char *s2, int n);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int execute(buf_struct *a, char *path);
void error_cd(buf_struct *a, char buffer[]);
void _error(buf_struct *a, char buffer[]);
int _itoa(int n, char buf[]);
long _atoi(char *s);
int _strlen(char *s);
void *_memset(void *s, char c, unsigned int len);
char *_memcpy(char *dest, char *src, unsigned int n);

#endif
