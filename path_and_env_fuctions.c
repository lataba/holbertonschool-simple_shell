#include "shell.h"

/**
 * store_tokens - Funcion that separates the line in arguments
 * @line: The line that user writes on the stdin
 * Return: A double poniter to an array that stores the arguments (tokens)
 */

char **store_tokens(char *line)
{
	char **array_tok = NULL, *token = NULL;
	int i = 0, line_len = 0, j = 0;

	if (line == NULL)
		return (NULL);

	line_len = str_count(line);

	if (line_len > 0)
	{
		array_tok = malloc(sizeof(char *) * (line_len + 1));
		if (array_tok == NULL)
			return (NULL);

		token = strtok(line, "\n\t ");
		while (token != NULL)
		{
			array_tok[i] = strdup(token);
			if (array_tok[i] == NULL)
			{
				for (j = 0; j <= i; j++)
					free(array_tok[j]);
				free(array_tok);
				free(token);
				return (NULL);
			}
			token = strtok(NULL, "\t\n ");
			i++;
		}
		array_tok[i] = NULL;
	}
	return (array_tok);
}

/**
 * str_count - Function that ounts the number of words in a string
 * @str: The line given by the user
 * Return: The number of words in the string line
 */
int str_count(char *str)
{
	int i = 0, count = 0;

	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			count++;
			i++;
			while (str[i] && str[i] != ' ')
				i++;
		}
	}
	return (count);
}

/**
 * get_env - Function that gets the value of enviroment variable.
 * @var_name: The name of the enviroment variable.
 * Return: The value of the environment Variable or NULL.
 */

char *get_env(char *var_name)
{
	int i = 0;
	char *var_value;
	size_t len_value, len_name = strlen(var_name);

	while (environ[i] != NULL)

	{
		len_value = strlen(environ[i]);
		var_value = malloc((len_value + 1) * sizeof(char));
		if (var_value == NULL)
		{
			perror("malloc");
			return (NULL);
		}
		if ((strncmp(var_name, environ[i], len_name) == 0)
				&& (environ[i][len_name + 1] == '='))
		{
			strcpy(var_value, environ[i]);
			return (var_value);
		}
		free(var_value);
		i++;
	}
	return (NULL);
}

/**
 * path_match -  Searchs for the command in the path
 * @array_tok: The array of tokens containing the user line command
 * Return: 0 if success, 1 if fail
 */
int path_match(char **array_tok)
{
	char *path, *fullpath, *path_value;
	struct stat ex;

	path = get_env("PATH");
	if (path == NULL)
		return (127);
	path_value = strtok(path, ":");
	while (path_value != NULL)
	{
		fullpath = fullpath_func(*array_tok, path_value);
		if (stat(fullpath, &ex) == 0)
		{
			free(array_tok[0]);
			*array_tok = strdup(fullpath);
			free(fullpath);
			free(path);
			return (0);
		}
		free(fullpath);
		path_value = strtok(NULL, ":");
	}
	free(path);

	return (1);
}

/**
 * fullpath_func - Function that concatenates the fullpath
 * @array_tok: The tokens
 * @path_value: The path value
 * Return: A pointer to the complete command
 */

char *fullpath_func(char *array_tok, char *path_value)
{
	char *command;
	size_t len = 0;

	len = strlen(path_value) + strlen(array_tok) + 2;
	command = malloc(sizeof(char) * len);
	if (command == NULL)
	{
		return (NULL);
	}

	memset(command, 0, len);

	command = strcat(command, path_value);
	command = strcat(command, "/");
	command = strcat(command, array_tok);

	return (command);
}
