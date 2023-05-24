#ifndef _SHELL_H_
#define _SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define USE_STRTOK 0
#define USE_GETLINE 0

#define CMD_AND		2
#define CMD_CHAIN	3
#define CMD_NORM	0
#define CMD_OR		1

#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024

#define HIST_MAX	4096
#define HIST_FILE	".shell_history"

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

extern char **environ;

/**
 * struct liststr - single list
 * @next: pointer to the next node
 * @num: number
 * @str: str
 */
typedef struct liststr
{
	char *str;
	int num;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains arguements to pass into function
 * @arg: string gotten from getline
 * @argv: array of strings generated
 * @status: return status of the latter  command
 * @cmd_buf: pointer address to cmd_buf
 * @cmd_buf_type: CMD
 * @readfd: fd from which to read input
 * @histcount: history line count
 * * @fname: filename of the program
 * @env: local copy of environ
 * @environ: modified copy of environ from LL
 * @history: history node
 * @alias: alias node
 * @env_changed: on
 * * @path: string path for current command
 * @argc: argument count
 * @line_count: error count
 * @err_num: error code for exit
 * @linecount_flag: count this input line if on
 */
typedef struct passinfo
{
	char *fname;
	char *arg;
	char **argv;
	char *path;
	char **environ;
	int argc;
	int env_changed;
	int status;
	int err_num;
	int linecount_flag;
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
	unsigned int line_count;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **cmd_buf;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contain a builtin string, function
 * @func: function
 * @type: builtin flag
 */
typedef struct builtin
{
	int (*func)(info_t *);
	char *type;
} builtin_table;

char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);

void find_cmd(info_t *);
void fork_cmd(info_t *);
int hsh(info_t *, char **);

int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);

int loophsh(char **);

void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);
char *_strdup(const char *);

char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
int _strlen(char *);
int _strcmp(char *, char *);

char **strtow2(char *, char);
char **strtow(char *, char *);

char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);

int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);
int is_delim(char, char *);

int bfree(void **);

void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);

int _myhistory(info_t *);
int _myalias(info_t *);

int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);

int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _erratoi(char *);
void print_error(info_t *, char *);

int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
ssize_t get_input(info_t *);

int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);

int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
char *get_history_file(info_t *info);
int write_history(info_t *info);

size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);

size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);

#endif
