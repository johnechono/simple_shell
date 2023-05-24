#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/**
 * struct liststr - linked list
 * @num: number
 * @str:  string
 * @next: next node pointer
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - struct pass info
 *@env: environ local copy
 *@environ: modified environ copy
 *@history: node of history
 *@alias: node of alias
 *@env_changed: changing environ
 *@status: last command return status
 *@cmd_buf: pointer address
 *@cmd_buf_type: cmd symbols
 *@readfd: read fd
 *@histcount: history count
 *@arg: getline generated string
 *@argv: argument vector
 *@path: current command path
 *@argc: argument count
 *@line_count: for counting errors
 *@err_num: number error code
 *@linecount_flag: flagginf line count
 *@fname: file name for the program
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	char **environ;
	int err_num;
	int linecount_flag;
	char *fname;
	int env_changed;
	int status;
	unsigned int line_count;
	list_t *env;
	list_t *history;
	list_t *alias;

	int readfd;
	int histcount;
	char **cmd_buf;
	int cmd_buf_type;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);
char *_strdup(const char *);

void find_cmd(info_t *);
void fork_cmd(info_t *);
int hsh(info_t *, char **);
int find_builtin(info_t *);

char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
int _strlen(char *);
int _strcmp(char *, char *);

char **strtow(char *, char *);
char **strtow2(char *, char);

int loophsh(char **);

void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);
void ffree(char **);

int _atoi(char *);
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);

char *convert_number(long int, int, int);
void remove_comments(char *);
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);

int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);

int _myhelp(info_t *);
int _myexit(info_t *);
int _mycd(info_t *);

int _myalias(info_t *);
int _myhistory(info_t *);

char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);

list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);

void set_info(info_t *, char **);
void free_info(info_t *, int);
void clear_info(info_t *);

int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
char *get_history_file(info_t *info);
int write_history(info_t *info);

int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);

size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);

char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);

int bfree(void **);

int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

void sigintHandler(int);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);

int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define USE_GETLINE 0
#define USE_STRTOK 0

#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

extern char **environ;

#endif
