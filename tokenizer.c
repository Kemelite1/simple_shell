#include "shell.h"
/**
 * break_pth - tokenizes to path
 * @find: array
 * @locate: current location
 * @size: size of space
 * Return: a 2D array of tokens
 */

char **break_pth(char **find, char *locate, int size)
{
	int i, ct, idx;
	char *new, *space;

	space = _malloc(sizeof(char) * size);
	space[0] = '\0';
        i = 0;
        ct = 1;

        while (locate[i] != '\0')
	{
		if (locate[i] == ':')
			ct++;
                i++;
	}
	ct++;
	find = _malloc(sizeof(char *) * ct);
	/* skip the PATH= */
	for (new = locate; *new != '='; new++);
        
	new++, idx = 0;
	do {
		if (*new == ':' || *new == '\0')
		{
			_strncat(space, "/", 1);
			find[idx] = _malloc(sizeof(char) * size);
			find[idx][0] = '\0';
			_strncat(find[idx], space, _strlen(space));
			idx++;
			space[0] = '\0';
		}
		else
		{
			_strncat(space, new, 1);
		}
			
	} while (*new++);
	find[idx] = _malloc(sizeof(char *));
	find[idx] = NULL;
	return (find);
}
/**
 * break_buffer - tokenize buff_t by inputting NULLs and filling **av
 * @cont: The buff_t with the command string
 * @array: Pointer to the command argument vector
 * Description: This function accepts a string such as 'ls -l' and changes
 *              it to 'ls\0-l'. It puts pointers to 'ls' and '-l' into *av
 */
void break_buffer(buff_t *cont, char ***array)
{
	int i, j, ident, w_s;

	size_x(cont->b_s + cont->bl_s, array);

	/* Build the argument vector from the given buff_t */
	i = cont->bl_s;
	j = 0;
	ident = 1;
	while (!input_finish(cont->b_s[i]))
	{
		w_s = is_w(cont->b_s[i]);
		if (ident && !w_s)
		{
			(*array)[j++] = cont->b_s + i;
			ident = 0;
		}
		if (w_s)
		{
			cont->b_s[i] = '\0';
			ident = 1;
		}
		i++;
	}
	(*array)[j] = NULL;
	/* If we end because of comments */
	if (cont->b_s[i] == '#')
		while (cont->b_s[i] != '\n' && cont->b_s[i] != '\0')
			i++;
	/* If we ended because of newline, we MAY have more content */
	if (cont->b_s[i] == '\n' && cont->b_s[i + 1] != '\0')
		cont->b_s[i] = ';';
	else if (cont->b_s[i] == '\n')
		cont->b_s[i] = '\0';
	/* If we ended because of flow control commands, */
	/* increment the buff_t point and add a null before the character */
	if (cont->b_s[i] == ';' || cont->b_s[i] == '|' || cont->b_s[i] == '&')
	{
		cont->bl_s += i - cont->bl_s;
		end_inp(cont->b_s + cont->bl_s);
		cont->bl_s++;
	}
	else
		cont->bl_s = 0;

}
