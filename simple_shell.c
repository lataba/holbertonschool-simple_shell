#include "shell.h"

/**
 * main - Simple shell
 * Return: Exit value
 */

int main(void)
{
	char *line = NULL, **command = NULL;
	int status = 0;
	size_t len = 0;
	ssize_t nread = 0;

	while (1)
	{
		len = 0;
		if (isatty(STDIN_FILENO) != 0)
			printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			{free(line);
			exit(status); }
		if (*line == 10)
			{free(line);
			continue; }
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		command = store_tokens(line);
		if (command != NULL)
		{
			status = builtin_execute(command);
			if (status == -1)
			{
				free_arr(command);
				free(line);
				exit(EXIT_SUCCESS);
			}
			if (status == 1)
				status = fork_child(command);
			free_arr(command);
		}
		free(line);
	}
	return (status);
}
