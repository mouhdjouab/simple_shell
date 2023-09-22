#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct list_strng - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct list_strng
{
	int num;
	char *str;
	struct list_strng *next;
} tail_list;

/**
 * struct passinfo - A structure containing pseudo-arguments for passing into a function
 *
 * This structure is designed to allow a uniform prototype for a function pointer struct.
 *
 * @arg: A string generated from getline containing arguments.
 * @argv: An array of strings generated from the 'arg'.
 * @path: A string representing the current command's path.
 * @argc: The argument count.
 * @line_counter: The error count.
 * @error_number: The error code for exit() calls.
 * @linecount_flag: If set, count this line of input.
 * @file_name: The program filename.
 * @env: A linked list that serves as a local copy of the 'environ' environment variables.
 * @environ: A custom modified copy of the 'environ' from the linked list 'env'.
 * @history: The history node.
 * @alias: The alias node.
 * @env_changed: A flag indicating whether 'environ' was changed.
 * @status: The return status of the last executed command.
 * @cmd_buffer: The address of a pointer to the command buffer; set when chaining commands.
 * @cmd_buf_type: The type of command (CMD_type) such as ||, &&, or ;.
 * @readfd: The file descriptor from which to read line input.
 * @histcount: The history line number count.
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	tail_list *env;
	tail_list *history;
	tail_list *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} t_info;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builed - contains a builed string and related function
 *@type: the builed command flag
 *@func: the function
 */
typedef struct builed
{
	char *type;
	int (*func)(t_info *);
} table_of_builtin;



int hsh(t_info *, char **);
int find_builtin(t_info *);
void find_cmd(t_info *);
void fork_cmd(t_info *);
int excuction_cmd_checker(t_info *, char *);
char *cher_duplicator(char *, int, int);
char *path_finder(t_info *, char *, char *);
int loophsh(char **);
void print_inputs_to_stderr(char *);
int print_char_to_stderr(char);
int print_c_to_fd(char c, int fd);
int print_input_str_to_fd(char *str, int fd);
int stringlength(char *);
int stringcomparison(char *, char *);
char *checkhaystack(const char *, const char *);
char *stringconcatenates(char *, char *);
char *stringcopy(char *, char *);
char *stringduplicate(const char *);
void puts_print(char *);
int put_print_char(char);
char *stringcopy_byn(char *, char *, int);
char *stringconcatenate_byn(char *, char *, int);
char *locate_char(char *, char);
char **split_string(char *, char *);
char **split_string2(char *, char);
char *memory_fills(char *, char, unsigned int);
void memory_free(char **);
void *realloc_memory(void *, unsigned int, unsigned int);
int free_pointer(void **);
int is_shell_interactive(t_info *);
int is_character_delimiter(char, char *);
int is_alpha_character(int);
int string_to_integer(char *);
int str_to_int(char *);
void print_custom_error(t_info *, char *);
int print_integer(int, int);
char *convert_to_string(long int, int, int);
void remove_first_comment(char *);
int shell_exit(t_info *);
int dir_change(t_info *);
int display_help(t_info *);
int display_history(t_info *);
int man_alias_op(t_info *);
ssize_t line_getter_input(t_info *);
int line_getter(t_info *, char **, size_t *);
void custom_handler(int);
void information_clear_op(t_info *);
void information_set_op(t_info *, char **);
void information_free_op(t_info *, int);
char *get_environment_variable(t_info *, const char *);
int print_environment(t_info *);
int set_environment_variable(t_info *);
int unset_environment_variable(t_info *);
int populate_environment_list(t_info *);
char **retrieve_environment(t_info *);
int remove_environment_variable(t_info *, char *);
int init_set_environment_variable(t_info *, char *, char *);
char *retrieve_path_to_histfile(t_info *info);
int make_histfile(t_info *info);
int histfile_reader(t_info *info);
int hist_builder(t_info *info, char *buf, int linecount);
int hist_renum(t_info *info);
tail_list *node_add_operation(tail_list **, const char *, int);
tail_list *node_add_operation_end(tail_list **, const char *, int);
size_t print_only_str_list(const tail_list *);
int node_deletion_at_index(tail_list **, unsigned int);
void list_free_operation(tail_list **);
size_t length_of_linked_list(const tail_list *);
char **cnvt_list_to_array(tail_list *);
size_t print_likedlist(const tail_list *);
tail_list *nodestarter(tail_list *, char *, char);
ssize_t node_at_index(tail_list *, tail_list *);
int delim_chain_checker(t_info *, char *, size_t *);
void chain_checker(t_info *, char *, size_t *, size_t, size_t);
int alias_replace_op(t_info *);
int var_replace_op(t_info *);
int str_replace_op(char **, char *);

#endif
