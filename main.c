#include "shell.h"

/**
* Entry point for the shell program.
*
* @param ac Argument count
* @param av Argument vector
* @return Returns 0 on success, 1 on error
*/
int main(int ac, char **av)
{
t_info info[] = { INFO_INIT };
int fileDesc = 2;

asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (fileDesc)
: "r" (fileDesc));

if (ac == 2)
{
fileDesc = open(av[1], O_RDONLY);
if (fileDesc == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
print_inputs_to_stderr(av[0]);
print_inputs_to_stderr(": 0: Can't open ");
print_inputs_to_stderr(av[1]);
print_char_to_stderr('\n');
print_char_to_stderr(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
info->readfd = fileDesc;
}
populate_environment_list(info);
histfile_reader(info);
hsh(info, av);
return (EXIT_SUCCESS);
}
