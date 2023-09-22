#include "shell.h"

/**
 * stringcopy_byn - Copy a string up to 'n' characters.
 * @destinat: Pointer to the destination string.
 * @sourc: Pointer to the source string.
 * @n: Maximum number of characters to copy.
 *
 * Description: This function copies at most 'n' characters from the source
 * string 'sourc' to the destination string 'destinat'.
 *
 * Return: A pointer to the destination string 'destinat'.
 */
char *stringcopy_byn(char *destinat, char *sourc, int n)
{
	int iter, juggle;
	char *s = destinat;

	iter = 0;
	while (sourc[iter] != '\0' && iter < n - 1)
	{
		destinat[iter] = sourc[iter];
		iter++;
	}
	if (iter < n)
	{
		juggle = iter;
		while (juggle < n)
		{
			destinat[juggle] = '\0';
			juggle++;
		}
	}
	return (s);
}

/**
 * stringconcatenate_byn - Concatenate two strings, with a limit of 'n' characters.
 * @destinate: Pointer to the first string.
 * @sourc: Pointer to the second string.
 * @n: Maximum number of characters to concatenate.
 *
 * Description: This function appends at most 'n' characters from the source
 * string 'sourc' to the end of the destination string 'destinate'.
 *
 * Return: A pointer to the destination string 'destinate'.
 */
char *stringconcatenate_byn(char *destinate, char *sourc, int n)
{
	int iter, juggle;
	char *s = destinate;

	iter = 0;
	juggle = 0;
	while (destinate[iter] != '\0')
		iter++;
	while (sourc[juggle] != '\0' && juggle < n)
	{
		destinate[iter] = sourc[juggle];
		iter++;
		juggle++;
	}
	if (juggle < n)
		destinate[iter] = '\0';
	return (s);
}

/**
 * locate_char - Locate a character in a string.
 * @s: Pointer to the string to be searched.
 * @c: Character to look for.
 *
 * Description: This function searches for the first occurrence of the character
 * 'c' in the string 's'.
 *
 * Return: A pointer to the first occurrence of 'c' in 's', or NULL if not found.
 */
char *locate_char(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
