#include "shell.h"

/**
* stringcopy - Copies the string pointed to by src, including the null byte,
*	to the buffer pointed to by dest.
* @destinate: Pointer to the destination string where the content is to be co
* pied.
* @sourc:	Pointer to the source of string to be copied.
*
* Return: Pointer to the destination string dest.
*/
char *stringcopy(char *dest, char *src)
{
int iter = 0;

if (dest == src || src == 0)
return (dest);
while (src[iter])
{
dest[iter] = src[iter];
iter++;
}
dest[iter] = 0;
return (dest);
}

/**
* stringduplicate - Returns a pointer to a newly allocated space in memory,
*	which contains a copy of the string pointed to by str.
* @str: Pointer to the string to be duplicated.
*
* * Return: Pointer to the duplicated string. It returns NULL if insufficient m
* emory was available.
*/

char *stringduplicate(const char *str)
{
int length = 0;
char *ret;

if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}

/**
*puts_print - Outputs a string to the console.
*@str: Pointer to the string to be printed.
*
* Return: Nothing.
*/
void puts_print(char *str)
{
int iter = 0;

if (!str)
return;
while (str[iter] != '\0')
{
put_print_char(str[iter]);
iter++;
}
}

/**
* put_print_char - Outputs a character to the console.
* @c: The character to be output.
*
* Return: On success, it returns the number of characters written.
*	On error, it returns -1, and errno is set appropriately.
*/
int put_print_char(char c)
{
static int iter;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || iter >= WRITE_BUF_SIZE)
{
write(1, buf, iter);
iter = 0;
}
if (c != BUF_FLUSH)
buf[iter++] = c;
return (1);
}
