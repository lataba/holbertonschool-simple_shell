#include "shell.h"

/**
 * shell_exit - Exits the shell
 * Return: void
 */

int shell_exit(void)
{
	return (-1);
}


/**
 * shell_env - prints environment
 * Return: void
 */

int shell_env(void)
{
	unsigned int i;

	i = 0;
	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}

/**
 **builtin_execute - executes the built in functions
 **@tokens: arguments being passed
 **Return: tokens
 **/
int builtin_execute(char **tokens)
{
	int status;
	unsigned int length;
	unsigned int num;
	unsigned int i;

	built_s builtin[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{NULL, NULL}
	};

	length = strlen(tokens[0]);

	num = shell_num_builtins(builtin);
	for (i = 0; i < num; i++)
	{
		if (strncmp(tokens[0], builtin[i].name, length) == 0)
		{
			status = (builtin[i].p)();
			return (status);
		}
	}
	return (1);
}

/**
 **shell_num_builtins - this check num built-ins
 **@builtin: takes the builtin to be counted
 **Return: num of built-ins
 **/

int shell_num_builtins(built_s builtin[])
{
	unsigned int i;

	i = 0;
	while (builtin[i].name != NULL)
		i++;

	return (i);
}
