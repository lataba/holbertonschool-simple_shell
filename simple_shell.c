#include "shell.h"

/**
 * main - Simple shell
 * Return: Exit value
 */

int main(void)
{
	char *line = NULL, **command = NULL;
	int built_status, path_status;
	size_t len = 0;
	ssize_t nread = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO) != 0)
			printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			{free(line);
			exit(errno); }
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (*line == 10)
			{free(line);
			continue; }
		command = store_tokens(line);
		if (command != NULL)
			{built_status = builtin_execute(command);
			if (built_status == 0 || built_status == -1)
				{free_arr(command);
				free(line); }
			if (built_status == 0)
				continue;
			if (built_status == -1)
				exit(EXIT_SUCCESS);
			path_status = path_match(command);
			if (path_status == 0)
				fork_child(command[0], command);
			free(line);
			free_arr(command); }
		else
			free(line);
	}
	return (0);
}
