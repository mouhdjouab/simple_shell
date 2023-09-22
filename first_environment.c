#include "shell.h"

/**
* print_environment - Prints the current environment variables.
* @info: Pointer to the parameter struct.
*
* Return: Always 0.
*/
int print_environment(t_info *info)
{
print_only_str_list(info->env);
return (0);
}

/**
* get_environment_variable - Retrieves the value of an environment variable.
* @info: Pointer to the parameter struct.
* @name: Name of the environment variable.
*
* Return: The value of the environment variable or NULL if not found.
*/
char *get_environment_variable(t_info *info, const char *name)
{
tail_list *node = info->env;
char *p;

while (node)
{
p = checkhaystack(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
* init_set_environment_variable - Initializes a new environment variable
*	or modifies an existing one.
* @info: Pointer to the parameter struct.
*
* Return: 0 on success, 1 on failure.
*/
int set_environment_variable(t_info *info)
{
if (info->argc != 3)
{
print_inputs_to_stderr("Incorrect number of arguements\n");
return (1);
}
if (init_set_environment_variable(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
* unset_environment_variable - Removes an environment variable.
* @info: Pointer to the parameter struct.
*
* Return: 0 on success, 1 on failure.
*/
int unset_environment_variable(t_info *info)
{
int i;

if (info->argc == 1)
{
print_inputs_to_stderr("Too few arguements.\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
remove_environment_variable(info, info->argv[i]);

return (0);
}

/**
* populate_environment_list - Populates the environment linked list.
* @info: Pointer to the parameter struct.
*
* Return: 0 on success.
*/
int populate_environment_list(t_info *info)
{
tail_list *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
node_add_operation_end(&node, environ[i], 0);
info->env = node;
return (0);
}
