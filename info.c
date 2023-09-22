#include "shell.h"

/**
* information_clear_op - Initializes an t_info struct.
* @info: Pointer to the t_info struct to be cleared.
*/
void information_clear_op(t_info *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}

/**
* information_set_op - Initializes an t_info struct with arguments.
* @info: Pointer to the t_info struct to be initialized.
* @av: Argument vector.
*/
void information_set_op(t_info *info, char **av)
{
int i = 0;

info->fname = av[0];
if (info->arg)
{
info->argv = split_string(info->arg, " \t");
if (!info->argv)
{

info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = stringduplicate(info->arg);
info->argv[1] = NULL;
}
}
for (i = 0; info->argv && info->argv[i]; i++)
;
info->argc = i;

alias_replace_op(info);
var_replace_op(info);
}
}

/**
* information_free_op - Frees the memory allocated for an t_info struct's fie
* lds.
* @info: Pointer to the t_info struct.
* @all: True if freeing all fields, otherwise, only specific fields are freed
* .
*/
void information_free_op(t_info *info, int all)
{
memory_free(info->argv);
info->argv = NULL;
info->path = NULL;
if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
list_free_operation(&(info->env));
if (info->history)
list_free_operation(&(info->history));
if (info->alias)
list_free_operation(&(info->alias));
memory_free(info->environ);
info->environ = NULL;
free_pointer((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
put_print_char(BUF_FLUSH);
}
}
