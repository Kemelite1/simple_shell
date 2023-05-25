#include "shell.h"
/**
 * new_sz - Gets the new length of a writ_e partitioned
 *               by ";", "||", "&&&", or "#".
 * @writ_e: The writ_e to check.
 *
 * Return: The new length of the writ_e.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t new_sz(char *writ_e)
{
	size_t i;
	ssize_t sz2 = 0;
	char cur, post;

	for (i = 0; writ_e[i]; i++)
	{
		cur = writ_e[i];
		post = writ_e[i + 1];
		if (cur == '#')
		{
			if (i == 0 || writ_e[i - 1] == ' ')
			{
				writ_e[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (cur == ';')
			{
				if (post == ';' && writ_e[i - 1] != ' ' && writ_e[i - 1] != ';')
				{
					sz2 += 2;
					continue;
				}
				else if (writ_e[i - 1] == ';' && post != ' ')
				{
					sz2 += 2;
					continue;
				}
				if (writ_e[i - 1] != ' ')
					sz2++;
				if (post != ' ')
					sz2++;
			}
			else
				logical_ops(&writ_e[i], &sz2);
		}
		else if (cur == ';')
		{
			if (i != 0 && writ_e[i - 1] != ' ')
				sz2++;
			if (post != ' ' && post != ';')
				sz2++;
		}
		sz2++;
	}
	return (sz2);
}
/**
 * new_inp - Gets a command from standard input.
 * @ll: A buffer to store the command.
 * @et: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *new_inp(char *ll, int *et)
{
	size_t n = 0;
	ssize_t see;
	char *prompt = "$ ";

	if (ll)
		free(ll);

	see = _getline(&ll, &n, STDIN_FILENO);
	if (see == -1)
		return (NULL);
	if (see == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (new_inp(ll, et));
	}

	ll[see - 1] = '\0';
	variable_replacement(&ll, et);
	handle_line(&ll, see);

	return (ll);
}
