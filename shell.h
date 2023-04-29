#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>

/*global variable containing the environ variables values*/

extern char **environ;

/**
 * struct built_s - list of builtins
 * @name: name of builtin function
 * @p: pointer to function
 *
 * Description: struct for builtin functions.
**/
typedef struct built_s
{
	char *name;
	int (*p)(void);
} built_s;

/*functions of the simple_shell*/

char **store_tokens(char *line);
int str_count(char *str);
char *get_env(char *var_name);
int path_match(char **array_tok);
char *fullpath_func(char *array_tok, char *path_value);
void free_arr(char **array);
int fork_child(char **array_tok);
int shell_env(void);
int shekk_exit(void);
int builtin_execute(char **tokens);
int shell_num_builtins(built_s builtin[]);

#endif
