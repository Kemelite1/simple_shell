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
	// for (i = 0, ct = 1; locate[i] != '\0'; i++)
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
			_strncat(space, new, 1);
	} while (*new++);
	find[idx] = _malloc(sizeof(char *));
	find[idx] = NULL;
	return (find);
}
/**
 * break_buffer - tokenize buffer by inputting NULLs and filling **av
 * @cont: The buffer with the command string
 * @array: Pointer to the command argument vector
 * Description: This function accepts a string such as 'ls -l' and changes
 *              it to 'ls\0-l'. It puts pointers to 'ls' and '-l' into *av
 */
void break_buffer(buffer *cont, char ***array)
{
	int i, j, ident, w_s;
	char dir;

	size_x(cont->buf + cont->bp, array);

	/* Build the argument vector from the given buffer */
	// for (i = cont->bp, j = 0, ident = 1; !input_finish(cont->buf[i]); i++)
	i = cont->bp;
	j = 0;
	ident = 1;
	while (!input_finish(cont->buf[i]))
	{
		w_s = is_w(cont->buf[i]);
		if (ident && !w_s)
		{
			(*array)[j++] = cont->buf + i;
			ident = 0;
		}
		if (w_s)
		{
			cont->buf[i] = '\0';
			ident = 1;
		}
		i++;
	}
	(*array)[j] = NULL;
	/* If we end because of comments */
	if (cont->buf[i] == '#')
		while (cont->buf[i] != '\n' && cont->buf[i] != '\0')
			i++;
	/* If we ended because of newline, we MAY have more content */
	if (cont->buf[i] == '\n' && cont->buf[i + 1] != '\0')
		cont->buf[i] = ';';
	else if (cont->buf[i] == '\n')
		cont->buf[i] = '\0';
	/* If we ended because of flow control commands, */
	/* increment the buffer point and add a null before the character */
	if (cont->buf[i] == ';' || cont->buf[i] == '|' || cont->buf[i] == '&')
	{
		cont->bp += i - cont->bp;
		end_inp(cont->buf + cont->bp);
		cont->bp++;
	}
	else
		cont->bp = 0;

}