#include "shell.h"
/**
 * aliase - wrapper function for checking and replacing aliases
 * @b: buff_t structure
 * @env_p: enviornment struct to pass along
 * Return: 1 on list_al replacement, 0 if no replacement
 */
int aliase(buff_t *b, list_e *env_p)
{
	static int stop = 2;
	int i, size;
	char *str, *strcpy;

	size = 0, i = 0;
	while (b->b_s[b->bl_s] == ' ' || b->b_s[b->bl_s] == '\t')
		b->bl_s++;
	while (!is_w(b->b_s[b->bl_s + size]))
		size++;

	str = _malloc(sizeof(char) * (size + 1));
	strcpy = str;

	while (i < size)
		str[i] = b->b_s[b->bl_s + i], i++;
	str[i] = '\0';

	_a_shell(&str, env_p, 0);

	if (str)
	{
		rem_str(b, b->bl_s);
		add_str(b, str, b->bl_s);
		_free(strcpy);
		if (stop++ == 10)
		{
			stop = 0;
			return (0);
		}
		return (1);
	}
	else
		_free(str);
	stop = 0;
	return (0);
}
/**
 * a_operations - operates and configure for the list_al
 * @list: list_al
 * @arr: args
 *
 * Return: Always 0;
 */
int a_operations(list_al *list, char **arr)
{
	list_al *item;
	char *character, *val;
	int i, j;

	val = _strstr(arr[1], "=");
	if (val != NULL)
		val++;

	val = duplicate(val);

	i = 0;
	j = 0;
	while (arr[1][i] != '=')
		i++;
	character = _malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		character[j] = arr[1][j];
		j++;
	}
	character[j] = '\0';

	while (list->next != NULL && !strictStringMatch(character, list->unq))
		list = list->next;
	if (list->unq == NULL || strictStringMatch(character, list->unq))
	{
		list->unq = character;
		list->hold_s = val;
	}
	else if (list->next == NULL)
	{
		item = _malloc(sizeof(list_al));
		item->next = NULL;
		item->hold_s = val;
		item->unq = character;
		list->next = item;
	}
	else
		list->hold_s = val;
	return (0);
}
/**
 * a_print - print aliase
 * @list: linked list
 * @arr: args
 *
 * Return: 1 if no match needed, 2 on list_al not found, 0 on success
 */
int a_print(list_al *list, char **arr)
{
	char *string;

	string = _strstr(arr[1], "=");
	if (string != NULL)
		return (EXIT_FAILURE);

	string = a_find(list, arr[1]);
	if (string == NULL)
	{
		_puts("list_al not found\n");
		return (2);
	}
	else
	{
		_puts("list_al ");
		_puts(arr[1]);
		_puts("='");
		_puts(string);
		_puts("'\n");
	}
	return (EXIT_SUCCESS);
}
/**
 * a_complete - show all aliases
 * @prop: list_al linked list
 *
 * Return: Always 0
 */
int a_complete(list_al *prop)
{
	for ( ;prop != NULL && prop->unq != NULL; prop = prop->next)
	{
		_puts("list_al ");
		_puts(prop->unq);
		_puts("='");
		_puts(prop->hold_s);
		_puts("'\n");
	}
	return (EXIT_SUCCESS);
}
/**
 * a_find - find list_al values matching their unq
 * @prop: list_al linked list
 * @arr: list_al to search for
 *
 * Return: matching list_al hold_s, or NULL
 */
char *a_find(list_al *prop, char *arr)
{
	for (; prop != NULL && prop->unq != NULL; prop = prop->next)
	{
		if (strictStringMatch(arr, prop->unq))
			return (prop->hold_s);
	}
	return (NULL);
}
