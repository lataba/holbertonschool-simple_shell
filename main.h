#ifndef simple_shell
#define simple_shell
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

/* prototipos */
void ig_ctrlc(int signum);
int comands(char **argv);
int genv(void);
extern char **environ;
#endif
