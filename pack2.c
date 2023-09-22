#include "shell.h"

/**
 * str_to_int - Convert a string to an integer
 * @s: The string to be converted
 * Return: The converted number if successful, -1 on error
 */
int str_to_int(char *s)
{
	int iter = 0;
	unsigned long int rst = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (iter = 0;  s[iter] != '\0'; iter++)
	{
		if (s[iter] >= '0' && s[iter] <= '9')
		{
			rst *= 10;
			rst += (s[iter] - '0');
			if (rst > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rst);
}

/**
 * print_custom_error - Print an error message
 * @info: Information about the error
 * @estr: The error message to print
 */
void print_custom_error(t_info *info, char *estr)
{
	print_inputs_to_stderr(info->fname);
	print_inputs_to_stderr(": ");
	print_integer(info->line_count, STDERR_FILENO);
	print_inputs_to_stderr(": ");
	print_inputs_to_stderr(info->argv[0]);
	print_inputs_to_stderr(": ");
	print_inputs_to_stderr(estr);
}

/**
 * print_integer - Print an integer to a file descriptor
 * @input: The integer to print
 * @fd: The file descriptor to write to
 * Return: Number of characters printed
 */
int print_integer(int input, int fd)
{
	int (*__putchar)(char) = put_print_char;
	int iter, counter = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = print_char_to_stderr;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (iter = 1000000000; iter > 1; iter /= 10)
	{
		if (_abs_ / iter)
		{
			__putchar('0' + current / iter);
			counter++;
		}
		current %= iter;
	}
	__putchar('0' + current);
	counter++;

	return (counter);
}

/**
 * convert_to_string - Convert a number to a string representation
 * @num: The number to convert
 * @base: The base of the number (e.g., 10 for decimal)
 * @flags: Argument flags
 * Return: The string representation of the number
 */
char *convert_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_first_comment - Replace the first instance of '#' with '\0'
 * @buf: The string to modify
 */
void remove_first_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
