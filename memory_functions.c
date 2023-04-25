#include "shell.h"

/**
 * free_arr - Frees an array of char pointers
 * @array: The array to be free
 */
void free_arr(char **array)
{
	int i;

	i = 0;
	for (i = 0; array[i] ; i++)
		free(array[i]);
	free(array);
}


/**
 * re_alloc - Function that changes de size of a memory block
 * @block: Block to be expand
 * @old_size: Previous size of the block
 * @new_size: New size of the block
 * Return: Void pointer to the expanded block
 */
void *re_alloc(void *block, unsigned int old_size, unsigned int new_size)
{
	void *new_size_block;

	if (new_size == old_size)
		return (block);
	if (new_size == 0 && block)
	{
		free(block);
		return (NULL);
	}
	new_size_block = malloc(new_size);
	if ((new_size_block) == NULL)
		return (NULL);
	if (block == NULL)
	{
		memset(new_size_block, '\0', new_size);
		free(block);
	}
	else
	{
		memcpy(new_size_block, block, old_size);
		free(block);
	}
	return (new_size_block);
}
