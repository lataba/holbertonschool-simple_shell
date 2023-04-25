#include "shell.h"

/**
 * store_tokens - Funcion that separates the line in arguments
 * @line: The line that user writes on the stdin
 * Return: A double poniter to an array that stores the arguments (tokens)
 */

char **store_tokens(char *line)
{
	char **array_tok = NULL;
	char *token = NULL;
	int i = 0;

	if (line == NULL)
		return (NULL);

	array_tok = malloc(sizeof(char *));
	if (array_tok == NULL)
		return (NULL);

	token = strtok(line, "\n\t ");
	while (token != NULL)
	{
		array_tok[i] = strdup(token);
		if (array_tok[i] == NULL)
		{
			free_arr(array_tok);
			return (NULL); 
		}
		array_tok = re_alloc(*array_tok, sizeof(char *) * i, sizeof(char *) * (i + 1));
		if (array_tok == NULL)
		{
			free_arr(array_tok);
			return (NULL);
		}
		token = strtok(NULL, "\t\n ");
		i++;
	}
	array_tok[i] = NULL;
	return (array_tok);
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
		var_value = malloc(len_value * sizeof(char));
		if (var_value == NULL)
		{
			perror("failed to allocate value");
			return (NULL);
		}
		if (strncmp(var_name, environ[i], len_name) == 0 && strcpy(var_value, environ[i]))
		{
			return (var_value);
		}
		free(var_value);
		i++;
	}
	free(var_value);
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
	size_t len;
	struct stat file;

	path = get_env("PATH");
	path_value = strtok(path, ":");
	while (path_value != NULL)
	{
		len = strlen(path_value) + strlen(*array_tok) + 2;
		fullpath = malloc(sizeof(char)*len);
		if (fullpath == NULL) 
		{
			free(path);
			return (-1);
		}

		memset(fullpath, 0, len);
		fullpath = strcat(fullpath, path);
		fullpath = strcat(fullpath, "/");
		fullpath = strcat(fullpath, *array_tok);

		if (stat(fullpath, &file) == 0)
		{
			free(path);
			free(*array_tok);
			*array_tok = fullpath;
				return (0);
		}
		free(fullpath);
		path_value = strtok(NULL, ":");
	}
	free(path);
	return (1);
}
