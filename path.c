#include "shell.h"

/**
* excuction_cmd_checker - Checks if a file is an executable command.
* @info: Pointer to the info struct.
* @path: Path to the file.
*
* Return: 1 if true, 0 otherwise.
*/
int excuction_cmd_checker(t_info *info, char *path)
{
struct stat st;

(void)info;
if (!path || stat(path, &st))
return (0);

if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
* cher_duplicator - Duplicates characters within a given range.
* @pathstr: The PATH string.
* @start: Starting index.
* @stop: Stopping index.
*
* Return: Pointer to a new buffer.
*/
char *cher_duplicator(char *pathstr, int start, int stop)
{
static char buf[1024];
int iter = 0, k = 0;

for (k = 0, iter = start; iter < stop; iter++)
if (pathstr[iter] != ':')
buf[k++] = pathstr[iter];
buf[k] = 0;
return (buf);
}

/**
* path_finder - Finds the specified command in the PATH string.
* @info: Pointer to the info struct.
* @pathstr: The PATH string.
* @cmd: The command to find.
*
* Return: Full path of cmd if found, or NULL if not found.
*/
char *path_finder(t_info *info, char *pathstr, char *cmd)
{
int iter = 0, curr_position = 0;
char *path;

if (!pathstr)
return (NULL);
if ((stringlength(cmd) > 2) && checkhaystack(cmd, "./"))
{
if (excuction_cmd_checker(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[iter] || pathstr[iter] == ':')
{
path = cher_duplicator(pathstr, curr_position, iter);
if (!*path)
stringconcatenates(path, cmd);
else
{
stringconcatenates(path, "/");
stringconcatenates(path, cmd);
}
if (excuction_cmd_checker(info, path))
return (path);
if (!pathstr[iter])
break;
curr_position = iter;
}
iter++;
}
return (NULL);
}
