#include "shell.h"
/**
 * add_node - add a node to ist
 * @list: list
 * @newnode: new node
 */
void add_node(addr_list *list, void *newnode)
{
	addr_list *new = malloc(sizeof(addr_list));

	// if (new == NULL)
	if (!new)
	{
		_puts("Out of Memory, Exiting (._.)\n");
		_setfree(FREE_ADDRESSES);
		_exit(4);
	}
	new->address = newnode;
	new->next = list->next;
	list->next = new;
}
/**
 * free_list - free list
 * @list: list
 */
void free_list(addr_list *list)
{
	addr_list *new;

	// while (list != NULL)
	while (list)
	{
		new = list;
		list = list->next;
		if (new->address != NULL)
			free(new->address);
		free(new);
	}
}
/**
 * rem_node - remove data from node
 * @list: list
 * @addr: data it searches for
 *
 * Return: 0 if address is found and cleared, 1 if no match is found
 */
int rem_node(addr_list *list, void *addr)
{
	// while (list != NULL)
	while (list)
	{
		if (list->address == addr)
		{
			list->address = NULL;
			return (0);
		}
		list = list->next;
	}
	return (1);
}