#include "shell.h"

/**
 * memory_fills - Fills aaa memory block with aaa specified byte value.
 * @s: A pointer to the memory block.
 * @b: The byte value to fill the memory block with.
 * @n: The number of bytes to be filled.
 *
 * Return: A pointer to the memory block @s.
 */
char *memory_fills(char *s, char b, unsigned int n)
{
	unsigned int iter;

	for (iter = 0; iter < n; iter++)
		s[iter] = b;
	return (s);
}

/**
 * memory_free - Frees the memory occupied by an array of strings.
 * @pp: An array of strings to free.
 */
void memory_free(char **pp)
{
	char **aaa = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(aaa);
}

/**
 * realloc_memory - Reallocates a block of memory.
 * @ptr: A pointer to the previous memory block.
 * @old_size: The size (in bytes) of the previous memory block.
 * @new_size: The size (in bytes) of the new memory block.
 *
 * Return: A pointer to the newly reallocated memory block.
 */
void *realloc_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	ptr = malloc(new_size);
	if (!ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (ptr);
}
