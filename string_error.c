#include "shell.h"

/**
 * print_inputs_to_stderr - Prints an input string to stderr.
 * @str: The string to be printed.
 *
 * This function prints the input string to the standard error stream (stderr).
 * If the input string is NULL or empty, it does nothing.
 */
void print_inputs_to_stderr(char *str)
{
	int iter = 0;

	if (!str)
		return;
	while (str[iter] != '\0')
	{
		print_char_to_stderr(str[iter]);
		iter++;
	}
}

/**
 * print_char_to_stderr - Writes a character to stderr.
 * @c: The character to print.
 *
 * This function writes the given character to the standard error stream (stderr).
 * It uses a buffer to optimize the write operation. If the character is a special
 * value (BUF_FLUSH) or the buffer is full, it flushes the buffer to stderr.
 *
 * Return: On success, it returns 1. On error, -1 is returned, and errno is set appropriately.
 */
int print_char_to_stderr(char c)
{
	static int iter;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || iter >= WRITE_BUF_SIZE)
	{
		write(2, buf, iter);
		iter = 0;
	}
	if (c != BUF_FLUSH)
		buf[iter++] = c;
	return (1);
}

/**
 * print_c_to_fd - Writes a character to a given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * This function writes the given character to the specified file descriptor.
 * It also uses a buffer to optimize the write operation. If the character is a
 * special value (BUF_FLUSH) or the buffer is full, it flushes the buffer to the
 * specified file descriptor.
 *
 * Return: On success, it returns 1. On error, -1 is returned, and errno is set appropriately.
 */
int print_c_to_fd(char c, int fd)
{
	static int iter;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || iter >= WRITE_BUF_SIZE)
	{
		write(fd, buf, iter);
		iter = 0;
	}
	if (c != BUF_FLUSH)
		buf[iter++] = c;
	return (1);
}

/**
 * print_input_str_to_fd - Prints an input string to a specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * This function prints the input string to the specified file descriptor.
 * If the input string is NULL or empty, it returns 0. Otherwise, it returns
 * the number of characters successfully written.
 */
int print_input_str_to_fd(char *str, int fd)
{
	int iter = 0;

	if (!str)
		return (0);
	while (*str)
	{
		iter += print_c_to_fd(*str++, fd);
	}
	return (iter);
}
