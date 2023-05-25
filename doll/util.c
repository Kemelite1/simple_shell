#include "shell.h"
/**
 * dig_ct - Counts the digit length of a number.
 * @dig: The number to measure.
 *
 * Return: The digit length.
 */
int dig_ct(int dig)
{
	unsigned int dig2;
	int len = 1;

	if (dig < 0)
	{
		len++;
		dig2 = dig * -1;
	}
	else
	{
		dig2 = dig;
	}
	while (dig2 > 9)
	{
		len++;
		dig2 /= 10;
	}

	return (len);
}

/**
 * mk_err - Writes a custom term message to stderr.
 * @conts: An array of arguments.
 * @trash: The term value.
 *
 * Return: The term value.
 */
int mk_err(char **conts, int trash)
{
	char *term;

	switch (trash)
	{
	case -1:
		term = error_env(conts);
		break;
	case 1:
		term = error_1(conts);
		break;
	case 2:
		if (*(conts[0]) == 'e')
			term = error_2_exit(++conts);
		else if (conts[0][0] == ';' || conts[0][0] == '&' || conts[0][0] == '|')
			term = error_2_syntax(conts);
		else
			term = error_2_cd(conts);
		break;
	case 126:
		term = error_126(conts);
		break;
	case 127:
		term = error_127(conts);
		break;
	}
	write(STDERR_FILENO, term, _strlen(term));

	if (term)
		free(term);
	return (trash);

}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int num)
{
	char *buffer;
	int len = num_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}
/**
 * rework - Checks a lnt for logical operators "||" or "&&".
 * @lnt: A pointer to the character to check in the lnt.
 * @wl: Pointer to wl in get_new_len function.
 */
void rework(char *lnt, ssize_t *wl)
{
	char old, cur, post;

	old = *(lnt - 1);
	cur = *lnt;
	post = *(lnt + 1);

	if (cur == '&')
	{
		if (post == '&' && old != ' ')
			(*wl)++;
		else if (old == '&' && post != ' ')
			(*wl)++;
	}
	else if (cur == '|')
	{
		if (post == '|' && old != ' ')
			(*wl)++;
		else if (old == '|' && post != ' ')
			(*wl)++;
	}
}
/**
 * p_input - Partitions a ms see from standard input as needed.
 * @ms: A pointer to a ms see from standard input.
 * @see: The length of ms.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void p_input(char **ms, ssize_t see)
{
	char *prev_l, *sharps;
	char prev_h, cur, post;
	size_t i, j;
	ssize_t sz;

	sz = get_new_len(*ms);
	if (sz == see - 1)
		return;
	sharps = malloc(sz + 1);
	if (!sharps)
		return;
	j = 0;
	prev_l = *ms;
	for (i = 0; prev_l[i]; i++)
	{
		cur = prev_l[i];
		post = prev_l[i + 1];
		if (i != 0)
		{
			prev_h = prev_l[i - 1];
			if (cur == ';')
			{
				if (post == ';' && prev_h != ' ' && prev_h != ';')
				{
					sharps[j++] = ' ';
					sharps[j++] = ';';
					continue;
				}
				else if (prev_h == ';' && post != ' ')
				{
					sharps[j++] = ';';
					sharps[j++] = ' ';
					continue;
				}
				if (prev_h != ' ')
					sharps[j++] = ' ';
				sharps[j++] = ';';
				if (post != ' ')
					sharps[j++] = ' ';
				continue;
			}
			else if (cur == '&')
			{
				if (post == '&' && prev_h != ' ')
					sharps[j++] = ' ';
				else if (prev_h == '&' && post != ' ')
				{
					sharps[j++] = '&';
					sharps[j++] = ' ';
					continue;
				}
			}
			else if (cur == '|')
			{
				if (post == '|' && prev_h != ' ')
					sharps[j++]  = ' ';
				else if (prev_h == '|' && post != ' ')
				{
					sharps[j++] = '|';
					sharps[j++] = ' ';
					continue;
				}
			}
		}
		else if (cur == ';')
		{
			if (i != 0 && prev_l[i - 1] != ' ')
				sharps[j++] = ' ';
			sharps[j++] = ';';
			if (post != ' ' && post != ';')
				sharps[j++] = ' ';
			continue;
		}
		sharps[j++] = prev_l[i];
	}
	sharps[j] = '\0';

	free(*ms);
	*ms = sharps;
}
