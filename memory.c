#include "shell.h"
/**
 * _realloc - allocated to buff_t
 * @str: pointer 
 */
void _realloc(buff_t *str)
{
	char *temp;

	temp = str->b_s;
	str->sz *= 2;
	str->b_s = _malloc(sizeof(char) * str->sz);
	_memcpy(str->b_s, temp, str->sz / 2);
	_free(temp);
}
/**
 * _free - frees memory
 * @address: address
 */
void _free(void *address)
{
	_setfree(address);
	free(address);
}
/**
 * _setfree - free on exit,
 * @addr: loc 
 */
void _setfree(void *addr)
{
	static list_a list = {NULL, NULL};
	list_a *tmp;

	tmp = &list;
	if (addr != FREE_ADDRESSES && rem_node(tmp, addr))
	{
		while (1)
		{
			if (tmp->loc == NULL)
			{
				tmp->loc = addr;
				return;
			}
			else if (tmp->nxt == NULL)
			{
				add_node(tmp, addr);
				return;
			}
			tmp = tmp->nxt;
		}
	}
	else if (addr == FREE_ADDRESSES)
	{
		free_list(list.nxt);
		if (list.loc != NULL)
			free(list.loc);
	}
}
/**
 * _malloc - allocates memory and handles errors
 * @ptr_size: ptr_size of space to allocate
 *
 * Return: pointer to new space
 */
void *_malloc(size_t ptr_size)
{
	void *tmp;

	tmp = malloc(ptr_size);
	if (tmp == NULL)
	{
		_puts("Out of Memory, Exiting (._.)\n");
		_setfree(FREE_ADDRESSES);
		_exit(4);
	}
	_setfree(tmp);
	return (tmp);
}