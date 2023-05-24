#include "shell.h"
/**
 * size_x - resize
 * @cont: the buffer
 * @arr: array
 */
void size_x(char *cont, char ***arr)
{
	int j, i, ident, w_s;

	// for (j = 0, ident = 1; !input_finish(*cont); cont++)
        j = 0;
        ident = 1;
        while (!input_finish(*cont))
	{
		w_s = is_w(*cont);
		if (ident && !w_s)
			ident = 0, j++;
		else if (w_s)
			ident = 1;
                cont++;
	}

	if (*arr != NULL)
	{
		// for (i = 0; (*arr)[i] != NULL; i++);
                i = 0;
                while ((*arr)[i] != NULL)
                        i++;
		if (j > i)
		{
			_free(*arr);
			*arr = _malloc(sizeof(char *) * (j + 1));
		}
		return;
	}
	else
		*arr = _malloc(sizeof(char *) * (j + 1));
}

/**
 * find_elem - gets specified element
 * @index: particulsar character
 * @array: array
 * Return: an array the nth element or null if failed
 */

char *find_elem(char *array, int index)
{
	int i, j, ct;
	char *cont;

	cont = _malloc(sizeof(char) * BUFSIZE);
	ct = 0;
	i = 0;
	j = 0;
	// for (i = 0, j = 0; array[i] != '\0' || ct <= index; i++)
	while (array[i] != '\0' || ct <= index)
	{
		if (array[i] == ' ' && ct == index - 1)
		{
			cont[j] = '\0';
			return (cont);
		}

		if (array[i] == ' ' && ct != index - 1)
			ct++;
		else if (array[i] != ' ' && ct == index - 1)
			cont[j++] = array[i];
		i++;
	}
	return (NULL);
}
/**
 * cur_pid - get cur
 * Return: str
 */

char *cur_pid(void)
{
	char locate[BUFSIZE], unique[BUFSIZE];
	char *pause, *ppid;
	pid_t cur;
	int file;

	locate[0] = unique[0] = '\0';
	cur = fork();
	if (cur == 0)
	{
		_setfree(FREE_ADDRESSES);
		_exit(0);
	}
	else
	{
		pause = _itoa(cur, 1);
		_strcat(locate, "/proc/");
		_strcat(locate, pause);
		_strcat(locate, "/stat");
		file = open(locate, O_RDONLY);
		if (file > 0)
		{
			read(file, unique, 100);
			ppid = find_elem(unique, 4);
		}
		wait(NULL);
	}
	return (ppid);
}
/**
 * _to_buff - to buffer
 * @base: buff
 * @environ: Environment
 * @rt: return value of previous command
 */
void _to_buff(buffer *base, env_t *environ, int rt)
{	
	char *pause;
	int i, j;


	j = i = 0;
	while ((i = findSubstringIndex(base->buf + base->bp + j, "$")) >= 0 &&
		i < findFirstCharacterIndex(base->buf + base->bp + j, "\n;&|"))
	{
		i += j;
		j = i + 1;
		if (base->buf[base->bp + i + 1] == '?')
		{
			pause = _itoa(rt, 1);
			rem_str(base, base->bp + i);
			add_str(base, pause, base->bp + i);
			_free(pause);
		}
		else if (base->buf[base->bp + i + 1] == '$')
		{
			rem_str(base, base->bp + i);
			pause =  cur_pid();
			add_str(base, pause, base->bp + i);
		}
		else if (!is_w(base->buf[base->bp + i + 1]))
		{
			pause = _del_nm(environ, base->buf + base->bp + i + 1, base->size);
			rem_str(base, base->bp + i);
			if (pause != NULL)
				add_str(base, pause, base->bp + i);
		}
	}
}