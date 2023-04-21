#include "main.h"

int main(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	int readline = 0;
	char **argv = NULL;
	char *token;
	int i = 0, size = 64;

	signal(SIGINT, ig_ctrlc);

	while(1)
	{
		printf("$ ");

		readline = getline(&line, &bufsize, stdin);

		if (readline == -1) /* si hay error en leer la entrada */
			break;

		if (line[0] == '\n') /* enter case */
			continue;

		token = strtok(line, " ");
		
		while(token != NULL)
		{
			size++;
			token = strtok(NULL, " ");
		}

		if (size == 0)
			continue;

		argv = malloc((size + 1) * sizeof(char *));
		
		if (!argv)
		{
			perror("error malloc");
			exit(EXIT_FAILURE);
		}

		token = strtok(line, " ");
		i = 0;

		while(token != NULL)
		{
			argv[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		argv[size] = NULL;

		if (strcmp(argv[0], "exit") == 0)
		{
			free(line);
			free(argv);
			exit(0);
		}

		if (strcmp(argv[0], "env") == 0)
			genv();

		comands(argv);
		free(argv);
	}
	free(line);
	return(0);
}

/**
 *ig_ctrlc - manejo de señales
 *
 *@signum: señal
 *
 */
void ig_ctrlc(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 *comands - ejecute comand
 *
 *@argv: argv
 *
 * Return: 0
 */

int comands(char **argv)
{
	int status = 0;
	pid_t pid;

	pid = fork();

	if (pid == -1)
	{
		perror("Error");
		return(1);
	}

	else if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}

	return(0);
}
