#include "shell.h"
/**
 * c_extra - checks if there are exta commands
 * @space: space
 * @rt: Return
 * Return: 1 if we have more commands to execute, 0 if we don't
 */
int c_extra(buff_t *space, int rt)
{
	if (space->bl_s == 0)
		return (0);

	while (space->b_s[space->bl_s] != '\0')
	{
		if (space->b_s[space->bl_s] == ';')
		{
			c_short(space);
			return (1);
		}
		if (space->b_s[space->bl_s] == '&' && rt == 0)
		{
			c_short(space);
			return (1);
		}
		if (space->b_s[space->bl_s] == '|' && rt != 0)
		{
			c_short(space);
			return (1);
		}
		space->bl_s++;
	}
	space->bl_s = 0;
	return (0);
}
/**
 * c_short - short
 * @space: space
 */
void c_short(buff_t *space)
{
	int chk;

	chk = 0;
	while (space->b_s[space->bl_s] == ';')
		space->bl_s++, chk = 1;
	if (chk)
		return;

	while (space->b_s[space->bl_s] == '|')
		space->bl_s++, chk = 1;
	if (chk)
		return;

	while (space->b_s[space->bl_s] == '&')
		space->bl_s++;
}
/**
 * main - hsh
 * @ac: argument count
 * @av: a list of all arguments
 * @environ: environmental variable list from the parent
 * Return: 0 on success.
 */
int main(int ac, char **av, char **environ)
{
	char **array;
	list_e *ev_n;
	int rt;
	buff_t b = {NULL, BUFSIZE, 0};
	(void)ac, (void)av, (void)environ;

	b.b_s = _malloc(sizeof(char) * b.sz);
	array = NULL;
	rt = 0;

	ev_n = mk_env();
	_checker("", ev_n, 'c');
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, _sig);
	while (1)
	{
		if (!c_extra(&b, rt))
		{
			_puts("$ ");
			get_line(&b, STDIN_FILENO, ev_n);
			_checker(b.b_s, ev_n, 'a');
		}
		while (aliase(&b, ev_n))
			;
		_to_buff(&b, ev_n, rt);
		read_file(&b, ev_n);
		break_buffer(&b, &array);
		if (array[0] == NULL)
			continue;
		rt = execute2(array, ev_n, b.sz);
		if (rt != 0 && rt != 2)
		{
			rt = exec_part(array, ev_n, b.sz);
		}
			
	}
	return (EXIT_SUCCESS);
}
