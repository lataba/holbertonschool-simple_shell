#include "main.h"

/**
*genv - get environment var
*Return: 0
*/
int genv(void)
{
	unsigned int c = 0, i = 0;

	for (; environ[i] != NULL; i++)
	{
		write(1, environ[c], strlen(environ[c]));
		write(1, "\n", 1);
		c++;
	}
	return (0);
}
