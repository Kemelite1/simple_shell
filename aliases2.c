#include "shell.h"
/**
 * _a_shell - builtin for list_al function
 * @arr: argument vector
 * @environ: env new
 * @type: Execution type for the program, 0 or !0
 * Description: Complicated parent function for the list_al functionality
 *				of hsh. Uses two modes to allow it being called from
 *				multiple points from within our program.
 * Return: 0 on success, 2 on failure.
 */
int _a_shell(char **arr, list_e *environ, int type)
{
	int result;
	static list_al new = {NULL, NULL, NULL};

	(void) environ;
	if (type == 0)
	{
		arr[0] = a_find(&new, arr[0]);
		return (0);
	}
	else
	{
		if (arr[1] == NULL)
			result = a_complete(&new);
		else if (arr[2] != NULL)
		{
			_puts("Error. Too many arguments.");
			return (2);
		}
		else
		{
			result = a_print(&new, arr);
			if (result == 1)
				result = a_operations(&new, arr);
		}
	}
	return (result);
}
