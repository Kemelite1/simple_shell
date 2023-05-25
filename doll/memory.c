#include "shell.h"
/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @pt: A pointer to the memory previously allocated.
 * @pre_sp: The size in bytes of the allocated space for pt.
 * @post_cp: The size in bytes for the new memory block.
 *
 * Return: If post_cp == pre_sp - pt.
 *         If post_cp == 0 and pt is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *_realloc(void *pt, unsigned int pre_sp, unsigned int post_cp)
{
	void *brns;
	char *dup_p, *fill;
	unsigned int index;

	if (post_cp == pre_sp)
		return (pt);

	if (pt == NULL)
	{
		brns = malloc(post_cp);
		if (brns == NULL)
			return (NULL);

		return (brns);
	}

	if (post_cp == 0 && pt != NULL)
	{
		free(pt);
		return (NULL);
	}

	dup_p = pt;
	brns = malloc(sizeof(*dup_p) * post_cp);
	if (brns == NULL)
	{
		free(pt);
		return (NULL);
	}

	fill = brns;

	for (index = 0; index < pre_sp && index < post_cp; index++)
		fill[index] = *dup_p++;

	free(pt);
	return (brns);
}
/**
 * buf_hand - Reassigns the pt variable for _getline.
 * @pt: A space to store an input string.
 * @n: The size of pt.
 * @space: The string to assign to pt.
 * @b: The size of space.
 */
void buf_hand(char **pt, size_t *n, char *space, size_t b)
{
	if (*pt == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*pt = space;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*pt = space;
	}
	else
	{
		_strcpy(*pt, space);
		free(space);
	}
}
/**
 * _getline - Reads input from a inr.
 * @llp: A spc to store the input.
 * @n: The size of llp.
 * @inr: The inr to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t _getline(char **llp, size_t *n, FILE *inr)
{
	static ssize_t in_p;
	ssize_t rt_val;
	char c = 'x', *spc;
	int r;

	if (in_p == 0)
		fflush(inr);
	else
		return (-1);
	in_p = 0;

	spc = malloc(sizeof(char) * 120);
	if (!spc)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && in_p == 0))
		{
			free(spc);
			return (-1);
		}
		if (r == 0 && in_p != 0)
		{
			in_p++;
			break;
		}

		if (in_p >= 120)
			spc = _realloc(spc, in_p, in_p + 1);

		spc[in_p] = c;
		in_p++;
	}
	spc[in_p] = '\0';

	assign_lineptr(llp, n, spc, in_p);

	rt_val = in_p;
	if (r != 0)
		in_p = 0;
	return (rt_val);
}

/**
 * del_s - Frees up memory taken by s_ts.
 * @s_ts: A null-terminated double pointer containing commands/arguments.
 * @in: A double pointer to the beginning of s_ts.
 */
void del_s(char **s_ts, char **in)
{
	size_t i;

	for (i = 0; s_ts[i] || s_ts[i + 1]; i++)
		free(s_ts[i]);

	free(in);
}
/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat fl, a space-delimited fl containing
 *              information about the current process. The PID is the
 *              first word in the fl. The function reads the PID into
 *              a spc and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_t i = 0;
	char *spc;
	ssize_t fl;

	fl = open("/proc/self/stat", O_RDONLY);
	if (fl == -1)
	{
		perror("Cant read fl");
		return (NULL);
	}
	spc = malloc(120);
	if (!spc)
	{
		close(fl);
		return (NULL);
	}
	read(fl, spc, 120);
	while (spc[i] != ' ')
		i++;
	spc[i] = '\0';

	close(fl);
	return (spc);
}