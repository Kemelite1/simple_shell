#include "shell.h"

/**
 * exec_p - Calls the execution of a command.
 * @arr: An array of arguments.
 * @face: A double pointer to the beginning of arr.
 * @tr: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int exec_p(char **arr, char **face, int *tr)
{
	int rem, i;
	int (*builtin)(char **arr, char **face);

	builtin = get_builtin(arr[0]);

	if (builtin)
	{
		rem = builtin(arr + 1, face);
		if (rem != EXIT)
			*tr = rem;
	}
	else
	{
		*tr = execute(arr, face);
		rem = *tr;
	}

	hist++;

	for (i = 0; arr[i]; i++)
		free(arr[i]);

	return (rem);
}

/**
 * exec_cl - Partitions operators from commands and calls them.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int exec_cl(char **args, char **front, int *exe_ret)
{
	int ret, index;

	if (!args[0])
		return (*exe_ret);
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);
	return (ret);
}