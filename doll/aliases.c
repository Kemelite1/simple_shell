#include "shell.h"

/**
 * al_rep - Goes through the arguments and replace any matching alias
 * with their value.
 * @arr: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **al_rep(char **arr)
{
	alias_t *new;
	int i;
	char *vl;

	if (_strcmp(arr[0], "alias") == 0)
		return (arr);
	for (i = 0; arr[i]; i++)
	{
		new = aliases;
		while (new)
		{
			if (_strcmp(arr[i], new->name) == 0)
			{
				vl = malloc(sizeof(char) * (_strlen(new->value) + 1));
				if (!vl)
				{
					free_args(arr, arr);
					return (NULL);
				}
				_strcpy(vl, new->value);
				free(arr[i]);
				arr[i] = vl;
				i--;
				break;
			}
			new = new->next;
		}
	}

	return (arr);
}
/**
 * shw_al - Prints the alias in the format name='value'.
 * @list: Pointer to an list.
 */
void shw_al(alias_t *list)
{
	char *str;
	int hin = _strlen(list->name) + _strlen(list->value) + 4;

	str = malloc(sizeof(char) * (hin + 1));
	if (!str)
		return;
	_strcpy(str, list->name);
	_strcat(str, "='");
	_strcat(str, list->value);
	_strcat(str, "'\n");

	write(STDOUT_FILENO, str, hin);
	free(str);
}
/**
 * prep_al - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @av: Name of the alias.
 * @vl: Value of the alias. First character is a '='.
 */
void prep_al(char *av, char *vl)
{
	alias_t *new = aliases;
	int hin, j, k;
	char *str;

	*vl = '\0';
	vl++;
	hin = _strlen(vl) - _strspn(vl, "'\"");
	str = malloc(sizeof(char) * (hin + 1));
	if (!str)
		return;
	for (j = 0, k = 0; vl[j]; j++)
	{
		if (vl[j] != '\'' && vl[j] != '"')
			str[k++] = vl[j];
	}
	str[k] = '\0';
	while (new)
	{
		if (_strcmp(av, new->name) == 0)
		{
			free(new->value);
			new->value = str;
			break;
		}
		new = new->next;
	}
	if (!new)
		add_alias_end(&aliases, av, str);
}
/**
 * alias_sh - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @arr: An array of arguments.
 * @ace: A double pointer to the beginning of arr.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int alias_sh(char **arr, char __attribute__((__unused__)) **ace)
{
	alias_t *new = aliases;
	int i, tr = 0;
	char *str;

	if (!arr[0])
	{
		while (new)
		{
			print_alias(new);
			new = new->next;
		}
		return (tr);
	}
	for (i = 0; arr[i]; i++)
	{
		new = aliases;
		str = _strchr(arr[i], '=');
		if (!str)
		{
			while (new)
			{
				if (_strcmp(arr[i], new->name) == 0)
				{
					print_alias(new);
					break;
				}
				new = new->next;
			}
			if (!new)
				tr = create_error(arr + i, 1);
		}
		else
			set_alias(arr[i], str);
	}
	return (tr);
}