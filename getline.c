#include "shell.h"

/**
* buffer_reader - Reads and buffers chained commands from standard input.
* @info: Parameter struct containing shell information.
* @buf: Address of the buffer to store the input.
* @len: Address of the length variable.
*
* Return: Number of bytes read.
*/
ssize_t buffer_reader(t_info *info, char **buf, size_t *len)
{
ssize_t bytesRead = 0;
size_t bufferLength = 0;

if (!*len)
{

free(*buf);
*buf = NULL;
signal(SIGINT, custom_handler);
#if USE_GETLINE
bytesRead = getline(buf, &bufferLength, stdin);
#else
bytesRead = line_getter(info, buf, &bufferLength);
#endif
if (bytesRead > 0)
{
if ((*buf)[bytesRead - 1] == '\n')
{
(*buf)[bytesRead - 1] = '\0';
bytesRead--;
}
info->linecount_flag = 1;
remove_first_comment(*buf);
hist_builder(info, *buf, info->histcount++);
{
*len = bytesRead;
info->cmd_buf = buf;
}
}
}
return (bytesRead);
}

/**
* line_getter_input - Gets a line of input minus the newline character.
* @info: Parameter struct containing shell information.
*
* Return: Number of bytes read.
*/
ssize_t line_getter_input(t_info *info)
{
static char *buf;
static size_t i, j, len;
ssize_t bytesRead = 0;
char **buf_p = &(info->arg), *p;
put_print_char(BUF_FLUSH);
bytesRead = buffer_reader(info, &buf, &len);
if (bytesRead == -1)
return (-1);
if (len)
{
j = i;
p = buf + i;
chain_checker(info, buf, &j, i, len);
while (j < len)
{
if (delim_chain_checker(info, buf, &j))
break;
j++;
}
i = j + 1;
if (i >= len)
{
i = len = 0;
info->cmd_buf_type = CMD_NORM;
}
*buf_p = p;
return (stringlength(p));
}
*buf_p = buf;
return (bytesRead);
}
/**
* buffer_reader_fromfd - Reads a buffer from a file descriptor.
* @info: Parameter struct containing shell information.
* @buf: Buffer to store the read data.
* @i: Size of the buffer.
*
* Return: Number of bytes read.
*/
ssize_t buffer_reader_fromfd(t_info *info, char *buf, size_t *i)
{
ssize_t bytesRead = 0;

if (*i)
return (0);
bytesRead = read(info->readfd, buf, READ_BUF_SIZE);
if (bytesRead >= 0)
*i = bytesRead;
return (bytesRead);
}

/**
* line_getter - Gets the next line of input from standard input.
* @info: Parameter struct containing shell information.
* @ptr: Address of a pointer to the buffer (preallocated or NULL).
* @length: Size of the preallocated buffer if not NULL.*
* Return: Number of bytes read.
*/
int line_getter(t_info *info, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;
p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;
r = buffer_reader_fromfd(info, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);
c = locate_char(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = realloc_memory(p, s, s ? s + k : k + 1);
if (!new_p)
return (p ? free(p), -1 : -1);
if (s)
stringconcatenate_byn(new_p, buf + i, k - i);
else
stringcopy_byn(new_p, buf + i, k - i + 1);
s += k - i;
i = k;
p = new_p;
if (length)
*length = s;
*ptr = p;
return (s);
}

/**
* custom_handler - Blocks the Ctrl-C signal and provides a custom handler.
* @sig_num: The signal number.
*
* Return: void
*/
void custom_handler(__attribute__((unused))int sig_num)
{
puts_print("\n");
puts_print("$ ");
put_print_char(BUF_FLUSH);
}
