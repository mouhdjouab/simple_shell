#include "shell.h"

/**
* display_history - Displays the history list, one command by line, preceded
*	with line numbers, starting at 0.
* @info: Structure containing potential arguments. Used to maintain
*	constant function prototype.
*
* Return: Always 0.
*/
int display_history(t_info *info)
{
print_likedlist(info->history);
return (0);
}

/**
* unset_alias_op - Sets alias to an empty string.
* @info: Parameter struct.
* @str: The string alias.
*
* Return: Always 0 on success, 1 on error.
*/
int unset_alias_op(t_info *info, char *str)
{
char *ptr, c;
int ret;

ptr = locate_char(str, '=');
if (!ptr)
return (1);
c = *ptr;
*ptr = 0;
ret = node_deletion_at_index(&(info->alias),
node_at_index(info->alias, nodestarter(info->alias, str, -1)));
*ptr = c;
return (ret);
}

/**
* set_alias_op - Sets alias to a string.
* @info: Parameter struct.
* @str: The string alias.
*
* Return: Always 0 on success, 1 on error.
*/
int set_alias_op(t_info *info, char *str)
{
char *ptr;

ptr = locate_char(str, '=');
if (!ptr)
return (1);
if (!*++ptr)
return (unset_alias_op(info, str));

unset_alias_op(info, str);
return (node_add_operation_end(&(info->alias), str, 0) == NULL);
}

/**
* show_alias_str - Prints an alias string.
* @node: The alias node.
*
* Return: Always 0 on success, 1 on error.
*/
int show_alias_str(tail_list *node)
{
char *ptr = NULL, *a = NULL;

if (node)
{
ptr = locate_char(node->str, '=');
for (a = node->str; a <= ptr; a++)
put_print_char(*a);
put_print_char('\'');
puts_print(ptr + 1);
puts_print("'\n");
return (0);
}
return (1);
}

/**
* man_alias_op - Mimics the alias build_in (man alias).
* @info: Structure containing potential arguments. Used to maintain
*	constant function prototype.
*
* Return: Always 0.
*/
int man_alias_op(t_info *info)
{
int i = 0;
char *ptr = NULL;
tail_list *node = NULL;

if (info->argc == 1)
{
node = info->alias;
while (node)
{
show_alias_str(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
ptr = locate_char(info->argv[i], '=');
if (ptr)
set_alias_op(info, info->argv[i]);
else
show_alias_str(nodestarter(info->alias, info->argv[i], '='));
}

return (0);
}
