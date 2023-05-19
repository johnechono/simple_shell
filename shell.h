#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

void _puts2(char *str);
char *_uitoa(unsigned int count);
void print_error(vars_t *vars, char *msg);

char *find_path(char **env);
int execute_cwd(vars_t *vars);
int check_for_dir(char *str);
void check_for_path(vars_t *vars);
int path_execute(char *command, vars_t *vars);

void _env(vars_t *vars);
void new_setenv(vars_t *vars);
void new_unsetenv(vars_t *vars);
void (*check_for_builtins(vars_t *vars))(vars_t *vars);
void new_exit(vars_t *vars);

char *add_value(char *key, char *value);
int _atoi(char *str);
void add_key(vars_t *vars);
char **find_key(char **env, char *key);

int _strcmpr(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);
ssize_t _puts(char *str);
char *_strdup(char *strtodup);

char **_realloc(char **ptr, size_t *size);
char *new_strtok(char *str, const char *delim);
char **tokenize(char *buffer, char *delimiter);

char **make_env(char **env);
void free_env(char **env);

/**
 * struct builtin - struct type for builtin function
 * @f: fnctn for builtin
 * @name: builtin command name
 */
typedef struct builtin
{
	char *name;
	void (*f)(vars_t *);
} builtin_t;

/**
 * struct variable - the variable
 * @count: command count
 * @argv: argument
 * @status: status of exit
 * @commands: command double pointer
 * @av: arguments of command line
 * @buffer: buffering command
 * @env: variables in the environ
 */
typedef struct variable
{
	char **argv;
	int status;
	char **commands;
	char **av;
	char *buffer;
	char **env;
	size_t count;
} vars_t;

#endif
