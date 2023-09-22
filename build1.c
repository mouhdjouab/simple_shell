#include "shell.h"

/**
* shell_exit - Exits the shell.
* @info: Structure containing potential arguments. Used to maintain
*	constant function prototype.
*
* Return: Exits with a given exit status (0) if info->argv[0] != "exit".
*/
int shell_exit(t_info *info)
{
int exit_check;

if (info->argv[1])	/* If there is an exit arguement */
{
exit_check = str_to_int(info->argv[1]);
if (exit_check == -1)
{
info->status = 2;
print_custom_error(info, "Illegal number: ");
print_inputs_to_stderr(info->argv[1]);
print_char_to_stderr('\n');
return (1);
}
info->err_num = str_to_int(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}

/**
* dir_change - Changes the current directory of the process.
* @info: Structure containing potential arguments. Used to maintain
*	constant function prototype.
*
* Return: Always 0.
*/
int dir_change(t_info *info)
{
char *s, *dir, buffer[1024];
int ch_dir_ret;
s = getcwd(buffer, 1024);
if (!s)
puts_print("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
dir = get_environment_variable(info, "HOME=");
if (!dir)
ch_dir_ret = /* TODO: what should this be? */
chdir((dir = get_environment_variable(info, "PWD=")) ? dir : "/");
else
ch_dir_ret = chdir(dir);
}
else if (stringcomparison(info->argv[1], "-") == 0)
{
if (!get_environment_variable(info, "OLDPWD="))
{
puts_print(s);
put_print_char('\n');
return (1);
}
puts_print(get_environment_variable(info, "OLDPWD=")), put_print_char('\n');
ch_dir_ret = /* TODO: what should this be? */
chdir((dir = get_environment_variable(info, "OLDPWD=")) ? dir : "/");
}
else
ch_dir_ret = chdir(info->argv[1]);
if (ch_dir_ret == -1)
{
print_custom_error(info, "can't cd to ");
print_inputs_to_stderr(info->argv[1]), print_char_to_stderr('\n');
}
else
{
init_set_environment_variable(info,
		"OLDPWD", get_environment_variable(info, "PWD="));
init_set_environment_variable(info,
		"PWD", getcwd(buffer, 1024));
}	return (0);
}

/**
* display_help - Displays help information. (Function not yet implemented)
* @info: Structure containing potential arguments. Used to maintain
*	constant function prototype.
*
* Return: Always 0.
*/
int display_help(t_info *info)
{
char **arg_array;

arg_array = info->argv;
puts_print("help call works. Function not yet implemented \n");
if (0)
puts_print(*arg_array); /* temp att_unused workaround */
return (0);
}
