#include "shell.h"

/**
* node_add_operation - Adds a node to the start of a linked list.
* @head: Address of a pointer to the head node.
* @str: String field of the new node.
* @num: Node index used by history.
*
* Return: A pointer to the newly created node or NULL on failure.
*/
tail_list *node_add_operation(tail_list **head, const char *str, int num)
{
tail_list *new_head;

if (!head)
return (NULL);
new_head = malloc(sizeof(tail_list));
if (!new_head)
return (NULL);
memory_fills((void *)new_head, 0, sizeof(tail_list));
new_head->num = num;
if (str)
{
new_head->str = stringduplicate(str);
if (!new_head->str)
{
free(new_head);
return (NULL);
}
}
new_head->next = *head;
*head = new_head;
return (new_head);
}

/**
* node_add_operation_end - Adds a node to the end of a linked list.
* @head: Address of a pointer to the head node.
* @str: String field of the new node.
* @num: Node index used by history.
*
* Return: A pointer to the newly created node or NULL on failure.
*/
tail_list *node_add_operation_end(tail_list **head, const char *str, int num)
{
tail_list *new_node, *node;

if (!head)
return (NULL);

node = *head;
new_node = malloc(sizeof(tail_list));
if (!new_node)
return (NULL);
memory_fills((void *)new_node, 0, sizeof(tail_list));
new_node->num = num;
if (str)
{
new_node->str = stringduplicate(str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}
if (node)
{
while (node->next)
node = node->next;
node->next = new_node;
}
else
*head = new_node;
return (new_node);
}

/**
* print_only_str_list - Prints only the str element of a tail_list linked lis
* t.
* @h: Pointer to the first node.
*
* Return: The size of the list.
*/
size_t print_only_str_list(const tail_list *h)
{
size_t i = 0;

while (h)
{
puts_print(h->str ? h->str : "(nil)");
puts_print("\n");
h = h->next;
i++;
}
return (i);
}

/**
* node_deletion_at_index - Deletes a node at the given index.
* @head: Address of a pointer to the first node.
* @index: Index of the node to delete.
*
* Return: 1 on success, 0 on failure.
*/
int node_deletion_at_index(tail_list **head, unsigned int index)
{
tail_list *node, *prev_node;
unsigned int i = 0;

if (!head || !*head)
return (0);

if (!index)
{
node = *head;
*head = (*head)->next;
free(node->str);
free(node);
return (1);
}
node = *head;
while (node)
{
if (i == index)
{
prev_node->next = node->next;
free(node->str);
free(node);
return (1);
}
i++;
prev_node = node;
node = node->next;
}
return (0);
}

/**
* list_free_operation - Frees all nodes of a list.
* @head_ptr: Address of a pointer to the head node.
*
* Return: void
*/
void list_free_operation(tail_list **head_ptr)
{
tail_list *node, *next_node, *head;

if (!head_ptr || !*head_ptr)
return;
head = *head_ptr;
node = head;
while (node)
{
next_node = node->next;
free(node->str);
free(node);
node = next_node;
}
*head_ptr = NULL;
}
