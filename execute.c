#include "shell.h"
/**
 * execute2 - execute builtin functions
 * @arr: array
 * @environ: enviorn list
 * @size_s: size
 * Return: 0 on found builtin, 1 on found nothing, 2 on builtin error
 */
int execute2(char **arr, list_e *environ, int size_s)
{
	int i, sz, pow;
	builtin table[] = {
	{"exit", exit_shell},     {"env", env_shell},
	{"setenv", setenv_shell}, {"unsetenv", unsetenv_shell},
	{"cd", cd_shell},         {"history", hist_shell},
	{"help", help_shell},     {"alias", _a_shell}
	};

	sz = ARRAY_SIZE(table);
        i = 0;

        while(i < sz)
	{
		if (strictStringMatch(arr[0], table[i].name))
		{
			pow = table[i].func(arr, environ, size_s);
			return (pow);
		}
                i++;
	}
	return (EXIT_FAILURE);
}
/**
 * main_execute - function that runs the execve system call.
 * @input: input
 * @array: array
 * @environ: environement
 * Return: 0 on success and 2 on failure
 */

int main_execute(char *input, char **array, list_e *environ)
{
	pid_t cur;
	int st, i;
	char **arr_s;



	cur = fork();
	if (cur == 0)
	{
		arr_s = arr_init(environ);

		i = execve(input, array, arr_s);
		if (i < 0)
		{
			_puts("Error: command not found\n");
			return (2);
			_exit(EXIT_FAILURE);
		}
	}
	else
	{

		cur = wait(&st);
		if (WIFEXITED(st))
			return (st);
	}
	return (2);
}
/**
 * exec_part - execute
 * @arr: array
 * @environ: environment
 * @input_s: size
 * Return: st if success or 127 if failure.
 */
int exec_part(char **arr, list_e *environ, int input_s)
{
	char *inp, *locate;
	char **find;
	int st, i, m;

	find = NULL;
	i = 0;
	inp = _malloc(sizeof(char) * input_s);
	locate = _malloc(sizeof(char) * input_s);
	_strcpy(inp, arr[0]);
	if (_strchr(inp, '/') != NULL)
		st = main_execute(inp, arr, environ);
	else
	{
		m = _pth(locate, environ);
		if (m != 0)
		{
			_puts("Error: Cannot find PATH variable\n");
			return (127);
		}
		find = break_pth(find, locate, input_s);
		i = mk_pth(inp, find);
		if (i == 0)
		{
			st = main_execute(inp, arr, environ);
		}
	}
	if (i == 0)
		return (st);
	else
		return (127);
}
/**
 * _sig - handles the ctrl-c signal
 * @s: signal received
 */

void _sig(int s)
{
	(void) s;
	_puts("\n");
	_puts("$ ");
}
