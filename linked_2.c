#include "shell.h"

/**
 * length_of_linked_list - Determines the length of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t length_of_linked_list(const tail_list *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * cnvt_list_to_array - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **cnvt_list_to_array(tail_list *head)
{
	tail_list *node = head;
	size_t i = length_of_linked_list(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(stringlength(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = stringcopy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_likedlist - Prints all elements of a tail_list linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_likedlist(const tail_list *h)
{
	size_t i = 0;

	while (h)
	{
		puts_print(convert_to_string(h->num, 10, 0));
		put_print_char(':');
		put_print_char(' ');
		puts_print(h->str ? h->str : "(nil)");
		puts_print("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * nodestarter - Returns a node whose string starts with a given prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match as a prefix.
 * @c: The next character after the prefix to match.
 *
 * Return: The matching node or NULL if not found.
 */
tail_list *nodestarter(tail_list *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = checkhaystack(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * node_at_index - Gets the index of a given node in a linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node whose index is to be found.
 *
 * Return: The index of the node or -1 if not found.
 */
ssize_t node_at_index(tail_list *head, tail_list *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
