#include "shell.h"
/**
 * _realloc - allocated to buffer
 * @str: pointer 
 */
void _realloc(buffer *str)
{
	char *temp;

	temp = str->buf;
	str->size *= 2;
	str->buf = _malloc(sizeof(char) * str->size);
	_memcpy(str->buf, temp, str->size / 2);
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
 * @addr: address 
 */
void _setfree(void *addr)
{
	static addr_list list = {NULL, NULL};
	addr_list *tmp;

	tmp = &list;
	if (addr != FREE_ADDRESSES && rem_node(tmp, addr))
	{
		while (1)
		{
			if (tmp->address == NULL)
			{
				tmp->address = addr;
				return;
			}
			else if (tmp->next == NULL)
			{
				add_node(tmp, addr);
				return;
			}
			tmp = tmp->next;
		}
	}
	else if (addr == FREE_ADDRESSES)
	{
		free_list(list.next);
		if (list.address != NULL)
			free(list.address);
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