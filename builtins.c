#include "shell.h"
/**
 * exit_shell - exit
 * @arr: arr given by user input
 * @environ: environmental linked list
 * @size: the size of path
 * Return: 0 on success;
 */
int exit_shell(char **arr, list_e *environ, int size)
{
	int var_e;
	(void) size;

	if (arr[1] != NULL)
	{
		if (!(is_digit(arr[1][0])))
		{
			/*_puts("exit: Expression Syntax.\n");*/
			return (2);
		}
	}
	var_e = _atoi(arr[1]);
	_checker("", environ, 'w');
	_setfree(FREE_ADDRESSES);
	_exit(var_e & 0377);
	return (EXIT_SUCCESS);
}
/**
 * help_shell - help
 * @arr: array;
 * Return: 0 if success and 2 if failed
 */
int help_shell(char **arr)
{
	int i, wh_t;
	builtin conts[] = {
	{"exit", help_exit},     {"env", help_env},
	{"setenv", help_setenv}, {"unsetenv", help_unsetenv},
	{"cd", help_cd},         {"history", help_hist},
	{"help", help_help},     {"alias", help_alias}
	};

	if (arr[1] == NULL)
	{
		_puts("help usage: help COMMAND\n    ");
		_puts("Prints out useful information on builtin commands\n");
		return (EXIT_SUCCESS);
	}
	else
	{
		wh_t = ARRAY_SIZE(conts);

                i = 0;
                while (i < wh_t)
		{
			if (strictStringMatch(arr[1], conts[i].name))
			{
				conts[i].func();
				return (0);
			}
                        i++;
		}
	}
	_puts("No help topics match your query\n");
	return (EXIT_FAILURE + 1);
}
/**
 * hist_shell - hist
 * @arr: argruments
 * @environ: environement
 * @type: type
 * Return: Always 0
 */
int hist_shell(char **arr, list_e *environ, int type)
{
	static list_h old_cmd = {NULL, NULL};

        switch (type)
        {
                case 0:
                        new_hist(&old_cmd, environ);
                        break;
                case 1:
                        add_to_list(&old_cmd, arr[0]);
                        break;
                case 2:
                        add_to_file(environ, &old_cmd);
                        break;
                default:
        		if (arr[1] != NULL)
        		{
        			_puts("Error: no such command\n");
        			return (2);
        		}
        		show_hist(&old_cmd);
                        break;
        }
	return (EXIT_SUCCESS);
}
/**
 * setenv_shell - builtin 
 * @arr: arr
 * @environ: environment
 * @size: size
 * Return: 0 on success and 1 on error
 */
int setenv_shell(char **arr, list_e *environ, int size)
{
	char *type;
	list_e *new;
	int fl, i, j;
	(void) size;

	if (arr[1] == NULL || arr[2] == NULL || arr[3] != NULL)
		return (2);
	if (!(is_alpha(arr[1][0])))
		return (2);
	/* set up all strings up*/
	j = _strlen(arr[2]);
	i = _strlen(arr[1]);
	type = _malloc(sizeof(char) * (i + j + 2));
	_memcpy(type, arr[1], i + 1);
	_strncat(type, "=", 1);
	new = environ;
	fl = 0; 

	while(new != NULL)
	{
		if (matchStrings(new->hold, type) != 0)
		{
			_strcat(type, arr[2]);
			new->hold = type;
			fl = 1;
		}
		new = new->next;
	}
	if (fl == 0)
	{
		_strcat(type, arr[2]);
		env_join(&environ, type);
	}
	return (EXIT_SUCCESS);
}
/**
 * unsetenv_shell - builtin 
 * @arr: args
 * @environ: environment
 * Return: 0 on success and 1 on failure
 * Description: This will delete the node that contains the variable given, if
 * node does not exist then function will succeed
 */
int unsetenv_shell(char **arr, list_e *environ)
{
	char *type;
	list_e *new;
	int ct, i;

	if (arr[1] == NULL)
	{
		/*_write("unsetenv: Too few arguments.\n");*/
		return (2);
	}
	i = _strlen(arr[1]);
	type = _malloc(sizeof(char) * (i + 2));
	_memcpy(type, arr[1], i + 1);
	_strncat(type, "=", 1);

	new = environ;
	ct = 0;
	while (new != NULL)
	{
		if (_strstr(new->hold, type) != NULL)
		{
			env_del(&environ, ct);
			return (0);
		}
		ct++;
		new = new->next;
	}
	return (2);
}
