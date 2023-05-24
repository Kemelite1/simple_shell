#include "shell.h"
/**
 * add_node - add a node to ist
 * @list: list
 * @newnode: new node
 */
void add_node(list_a *list, void *newnode)
{
	list_a *new = malloc(sizeof(list_a));

	if (new == NULL)
	{
		_puts("Out of Memory, Exiting (._.)\n");
		_setfree(FREE_ADDRESSES);
		_exit(4);
	}
	new->loc = newnode;
	new->nxt = list->nxt;
	list->nxt = new;
}
/**
 * free_list - free list
 * @list: list
 */
void free_list(list_a *list)
{
	list_a *new;

	while (list != NULL)
	{
		new = list;
		list = list->nxt;
		if (new->loc != NULL)
			free(new->loc);
		free(new);
	}
}
/**
 * rem_node - remove data from node
 * @list: list
 * @addr: data it searches for
 *
 * Return: 0 if loc is found and cleared, 1 if no match is found
 */
int rem_node(list_a *list, void *addr)
{
	while (list != NULL)
	{
		if (list->loc == addr)
		{
			list->loc = NULL;
			return (0);
		}
		list = list->nxt;
	}
	return (1);
}