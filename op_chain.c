#include "shell.h"

/**
* delim_chain_checker - checks if the current character in the buffer is a ch
* ain delimiter
* @info: the parameter struct
* @buf: the character buffer
* @p: address of the current position in buf
*
* Return: 1 if chain delimiter, 0 otherwise
*/
int delim_chain_checker(t_info *info, char *buf, size_t *p)
{
size_t juggle = *p;

if (buf[juggle] == '|' && buf[juggle + 1] == '|')
{
buf[juggle] = 0;
juggle++;
info->cmd_buf_type = CMD_OR;
}
else if (buf[juggle] == '&' && buf[juggle + 1] == '&')
{
buf[juggle] = 0;
juggle++;
info->cmd_buf_type = CMD_AND;
}
else if (buf[juggle] == ';') /* found end of this command */
{
buf[juggle] = 0; /* replace semicolon with null */
info->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*p = juggle;
return (1);
}

/**
* chain_checker - checks if we should continue chaining based on the last sta
* tus
* @info: the parameter struct
* @buf: the character buffer
* @p: address of the current position in buf
* @i: starting position in buf
* @len: length of buf
*
* Return: Void
*/
void chain_checker(t_info *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t juggle = *p;

if (info->cmd_buf_type == CMD_AND)
{
if (info->status)
{
buf[i] = 0;
juggle = len;
}
}
if (info->cmd_buf_type == CMD_OR)
{
if (!info->status)
{
buf[i] = 0;
juggle = len;
}
}

*p = juggle;
}

/**
* alias_replace_op - replaces an alias in the tokenized string
* @info: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int alias_replace_op(t_info *info)
{
int iter;
tail_list *node;
char *p;

for (iter = 0; iter < 10; iter++)
{
node = nodestarter(info->alias, info->argv[0], '=');
if (!node)
return (0);
free(info->argv[0]);
p = locate_char(node->str, '=');
if (!p)
return (0);
p = stringduplicate(p + 1);
if (!p)
return (0);
info->argv[0] = p;
}
return (1);
}

/**
* var_replace_op - replaces vars in the tokenized string
* @info: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int var_replace_op(t_info *info)
{
int iter = 0;
tail_list *node;

for (iter = 0; info->argv[iter]; iter++)
{
if (info->argv[iter][0] != '$' || !info->argv[iter][1])
continue;

if (!stringcomparison(info->argv[iter], "$?"))
{
str_replace_op(&(info->argv[iter]),
stringduplicate(convert_to_string(info->status, 10, 0)));
continue;
}
if (!stringcomparison(info->argv[iter], "$$"))
{
str_replace_op(&(info->argv[iter]),
stringduplicate(convert_to_string(getpid(), 10, 0)));
continue;
}
node = nodestarter(info->env, &info->argv[iter][1], '=');
if (node)
{
str_replace_op(&(info->argv[iter]),
stringduplicate(locate_char(node->str, '=') + 1));
continue;
}
str_replace_op(&info->argv[iter], stringduplicate(""));

}
return (0);
}

/**
* str_replace_op - replaces a string
* @old: address of the old string
* @new: new string
*
* Return: 1 if replaced, 0 otherwise
*/
int str_replace_op(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
