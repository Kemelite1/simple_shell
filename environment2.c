#include "shell.h"
/**
 * mk_env - creates a linked list with all environment
 * variables in the extern environ variable
 * Return: main of created list
 */
list_e *mk_env(void)
{
	list_e *main;
	int i = 0;

	main = NULL;

        while (environ[i] != NULL)
        {
		env_join(&main, environ[i]);
                i++;
        }
	return (main);
}
/**
 * cng_env - swith env
 * @environ: environment
 * @type: type
 * @new_char: hold
 * @size: size
 */
void cng_env(list_e *environ, char *type, char *new_char, int size)
{
	char *nan;
	list_e *new;

	nan = _malloc(sizeof(char) * size);
	_memset(nan, '\0', size);
	_strcat(nan, type);
	_strcat(nan, new_char);

        new = environ;
        while (new != NULL)
	{
		if (_strstr(new->hold, type) != NULL && new->hold[0] == type[0])
		{
			new->hold = nan;
			break;
		}
                new = new->next;
	}
}
/**
 * env_shw - shows vars
 * @main: main pointer to the linked list
 */

void env_shw(list_e *main)
{
	list_e *new;

        for (new = main; new != NULL; new = new->next)
	{
		_puts(new->hold);
		_puts("\n");
	}
}
/**
 * env_del - deletes
 * @main: pointer to the main of the linked list
 * @num: the nth node to delete
 */

void env_del(list_e **main, int num)
{
	list_e *new;
	list_e *new_s;
	int i;
	/*DEBUG: Shouldn't this just remove env by name, why by num?*/
	i = 0;
	new = *main;
	if (num == 0)
	{
		*main = (*main)->next;
		_free(new->hold);
		_free(new);
	}
	else
	{
                for (i = 0; i < num - 1; i++, new = new->next);
		new_s = new->next;
		new->next = new_s->next;
		_free(new_s);
	}
}
/**
 * env_join - joins another list item
 * @main: main of the linked list
 * @characters: environment
 * Return: the address of the new element, on fail, program exits
 */

list_e *env_join(list_e **main, char *characters)
{
	list_e *new;
	list_e *new_s;

	new = _malloc(sizeof(list_e));
	new->hold = duplicate(characters);
	new->next = NULL;
	if (*main == NULL)
		*main = new;
	else
	{
                for (new_s = *main; new_s->next != NULL; new_s = new_s->next);
		new_s->next = new;
	}
	return (new);
}
