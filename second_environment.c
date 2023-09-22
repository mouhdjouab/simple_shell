#include "shell.h"

/**
 * retrieve_environment - Retrieves the copy of the environment variables.
 * @info: Pointer to the parameter struct.
 *
 * Return: A copy of the environment variables as a string array.
 */
char **retrieve_environment(t_info *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = cnvt_list_to_array(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * remove_environment_variable - Removes an environment variable.
 * @info: Pointer to the parameter struct.
 * @var: The name of the environment variable to be removed.
 *
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int remove_environment_variable(t_info *info, char *var)
{
	tail_list *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = checkhaystack(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = node_deletion_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * init_set_environment_variable - Initializes a new environment variable or modifies an existing one.
 * @info: Pointer to the parameter struct.
 * @var: The name of the environment variable.
 * @value: The value to set for the environment variable.
 *
 * Return: 0 on success, 1 on failure.
 */
int init_set_environment_variable(t_info *info, char *var, char *value)
{
	char *buf = NULL;
	tail_list *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(stringlength(var) + stringlength(value) + 2);
	if (!buf)
		return (1);
	stringcopy(buf, var);
	stringconcatenates(buf, "=");
	stringconcatenates(buf, value);
	node = info->env;
	while (node)
	{
		p = checkhaystack(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	node_add_operation_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
