#include "shell.h"

/**
* stringlength - returns	length of	string
* @s:	string	length to check
*
* Return: integer length of string
*/

int stringlength(char *s)
{
int length = 0;

if (!s)
return (0);

while (*s++)
length++;
return (length);
}

/**
* stringcomparison - performs	comparison of two strings.
* @str1:	first string
* @str2:	second string
*
* * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 ==
*	s
* tr2
*/

int stringcomparison(char *str1, char *str2)
{
while (*str1 && *str2)
{
if (*str1 != *str2)
return (*str1 - *str2);
str1++;
str2++;
}
if (*str1 == *str2)
return (0);
else
return (*str1 < *str2 ? -1 : 1);
}

/**
* checkhaystack - checks if needle starts with haystack
* @haystack: string to search
* @needle: the substring to find
*
* Return: address of next char of haystack or NULL
*/
char *checkhaystack(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}

/**
* stringconcatenates - concatenates two strings
* @destinat: the destination buffer
* @source: the source buffer
*
* Return: pointer to destination buffer
*/
char *stringconcatenates(char *destinat, char *source)
{
char *ret = destinat;

while (*destinat)
destinat++;
while (*source)
*destinat++ = *source++;
*destinat = *source;
return (ret);
}
