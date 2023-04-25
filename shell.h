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

extern char **environ;

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv);
char **store_tokens(char *line);
int str_count(char *str);
char *get_env(char *var_name);
int path_match(char **array_tok);
char *fullpath_func(char *array_tok, char *path_value);
void free_arr(char **array);
int fork_child(char *fullpath, char **array_tok);

#endif
