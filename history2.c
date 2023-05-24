#include "shell.h"
/**
 * add_to_file - add to file
 * @environ: environement
 * @list: list
 * Return: 0 if success and 1 if failed to find pth for file
 */

int add_to_file(list_e *environ, list_h *list)
{
	list_h *new, *a_new;
	char *pth;
	int file, i;

	i = 0;

        a_new = list->next;
        while (a_new != NULL)
        {
                i++;
                a_new = a_new->next;
        }
	if (i > 4096)
	{
		i = i - 4096;
		while (i > 0)
		{
			list = list->next;
			i--;
		}
	}
	pth = _malloc(sizeof(char) * BUFSIZE);
	_memset(pth, '\0', BUFSIZE);
	pth = _del_nm(environ, "HOME=", BUFSIZE);
	if (pth == NULL)
	{
		_puts("Error: failed to find list file\n");
		_puts("Cannot write list\n");
		return (EXIT_FAILURE);
	}
	_strcat(pth, "/.simple_shell_history");
	file = open(pth, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	for (new = list; new != NULL; new = new->next)
	{
		write(file, new->in_p, _strlen(new->in_p));
		write(file, "\n", 1);
	}
	_free(list);
	close(file);
	return (EXIT_SUCCESS);
}
/**
 * _checker - checks
 * @input: input
 * @environ: environement
 * @type: type
 * Description: 'c' create type to create list,
 * 'a' add old_cmd type, and 'w' write to file type
 */

void _checker(char *input, list_e *environ, char type)
{
	char **str;

	str = _malloc(sizeof(char *) * 2);
        switch (type)
        {
                case 'c':
                        hist_shell(NULL, environ, 0);
                        break;
                case 'a':
                        str[0] = _malloc(sizeof(char) * (_strlen(input) + 1));
        		_memcpy(str[0], input, _strlen(input) + 1);
        		hist_shell(str, environ, 1);
			break;
                case 'w':
                        hist_shell(str, environ, 2);
			break;
                default:
                        break;
        }
}

/**
 * show_hist_2 - prints out the old_cmd with index
 * @old_cmd: old_cmd linked list
 */

void show_hist_2(list_h *old_cmd)
{
	int i, ct;
	char *string;
	list_h *new, *new_s;

	old_cmd = old_cmd->next;

	ct = 0;
	new = old_cmd;
	while (new != NULL)
	{
		ct++;
		new = new->next;
	}

	old_cmd = old_cmd->next;

	i = 0;
	new_s = old_cmd;
	while (new_s != NULL)
	{
		string = _itoa(i, 2);
		_puts(" ");
		_puts(string);
		_puts(" ");
		_puts(new_s->in_p);
		_puts("\n");
		new_s = new_s->next;
		i++;
	}
}
