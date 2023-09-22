#include "shell.h"

/**
* retrieve_path_to_histfile - Retrieves the path to the history file.
* @info: Pointer to the parameter struct.
*
* * Return: Allocated string containing the history file path, or NULL on failu
* re.
*/

char *retrieve_path_to_histfile(t_info *info)
{
char *buf, *dir;

dir = get_environment_variable(info, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (stringlength(dir) + stringlength(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
stringcopy(buf, dir);
stringconcatenates(buf, "/");
stringconcatenates(buf, HIST_FILE);
return (buf);
}

/**
* make_histfile - Creates a history file or appends to an existing one.
* @info: Pointer to the parameter struct.
*
* Return: 1 on success, -1 on failure.
*/
int make_histfile(t_info *info)
{
ssize_t fd;
char *file_name = retrieve_path_to_histfile(info);
tail_list *node = NULL;

if (!file_name)
return (-1);

fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(file_name);
if (fd == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
print_input_str_to_fd(node->str, fd);
print_c_to_fd('\n', fd);
}
print_c_to_fd(BUF_FLUSH, fd);
close(fd);
return (1);
}

/**
* histfile_reader - Reads history from a file and populates the history list.
* @info: Pointer to the parameter struct.
*
* Return: The number of history entries read, or 0 on failure.
*/
int histfile_reader(t_info *info)
{
int iter, lastofus = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *file_name = retrieve_path_to_histfile(info);

if (!file_name)
return (0);

fd = open(file_name, O_RDONLY);
free(file_name);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (iter = 0; iter < fsize; iter++)
if (buf[iter] == '\n')
{
buf[iter] = 0;
hist_builder(info, buf + lastofus, linecount++);
lastofus = iter + 1;
}
if (lastofus != iter)
hist_builder(info, buf + lastofus, linecount++);
free(buf);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
node_deletion_at_index(&(info->history), 0);
hist_renum(info);
return (info->histcount);
}

/**
* hist_builder - Adds an entry to the history linked list.
* @info: Pointer to the parameter struct.
* @buf: Buffer containing the history entry.
* @linecount: The history line count (histcount).
*
* Return: Always 0.
*/
int hist_builder(t_info *info, char *buf, int linecount)
{
tail_list *node = NULL;

if (info->history)
node = info->history;
node_add_operation_end(&node, buf, linecount);

if (!info->history)
info->history = node;
return (0);
}

/**
* hist_renum - Renumbers the history linked list after changes.
* @info: Pointer to the parameter struct.
*
* Return: The new histcount.
*/
int hist_renum(t_info *info)
{
tail_list *node = info->history;
int i = 0;

while (node)
{
node->num = i++;
node = node->next;
}
return (info->histcount = i);
}
