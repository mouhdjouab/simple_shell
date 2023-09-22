#include "shell.h"

/**
* hsh - main shell loop
* @info: the parameter & return info struct
* @av: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int hsh(t_info *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;

while (r != -1 && builtin_ret != -2)
{
information_clear_op(info);
if (is_shell_interactive(info))
puts_print("$ ");
print_char_to_stderr(BUF_FLUSH);
r = line_getter_input(info);
if (r != -1)
{
information_set_op(info, av);
builtin_ret = find_builtin(info);
if (builtin_ret == -1)
find_cmd(info);
}
else if (is_shell_interactive(info))
put_print_char('\n');
information_free_op(info, 0);
}
make_histfile(info);
information_free_op(info, 1);
if (!is_shell_interactive(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}

/**
* find_builtin - finds a builed command
* @info: the parameter & return info struct
*
* Return: -1 if builed not found,
*	0 if builed executed successfully,
*	1 if builed found but not successful,
*	-2 if builed signals exit()
*/
int find_builtin(t_info *info)
{
int i, built_in_ret = -1;
table_of_builtin builtintbl[] = {
{"exit", shell_exit},
{"env", print_environment},
{"help", display_help},
{"history", display_history},
{"setenv", set_environment_variable},
{"unsetenv", unset_environment_variable},
{"cd", dir_change},
{"alias", man_alias_op},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
if (stringcomparison(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[i].func(info);
break;
}
return (built_in_ret);
}

/**
* find_cmd - finds a command in PATH
* @info: the parameter & return info struct
*
* Return: void
*/
void find_cmd(t_info *info)
{
char *path = NULL;
int i, k;

info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!is_character_delimiter(info->arg[i], " \t\n"))
k++;
if (!k)
return;

path = path_finder(info,
		get_environment_variable(info, "PATH="),
		info->argv[0]);
if (path)
{
info->path = path;
fork_cmd(info);
}
else
{
if ((is_shell_interactive(info) || get_environment_variable(info, "PATH=")
|| info->argv[0][0] == '/') && excuction_cmd_checker(info, info->argv[0]))
fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_custom_error(info, "not found\n");
}
}
}

/**
* fork_cmd - forks a an exec thread to run cmd
* @info: the parameter & return info struct
*
* Return: void
*/
void fork_cmd(t_info *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, retrieve_environment(info)) == -1)
{
information_free_op(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_custom_error(info, "Permission denied\n");
}
}
}
