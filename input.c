#include "shell.h"
/**
 * _getline - Read input and put in buff_t
 * @b: buff_t 
 * @fd: file 
 * @envp: enviornment 
 * Return: Always 0. Exit on failure or EOF
 */
int get_line(buff_t *b, int fd, list_e *envp)
{
	int rack, n;

	rack = 0, n = 0;
	while ((n = read(fd, b->b_s + rack, b->sz - rack)) > 0 &&
			b->b_s[b->bl_s + rack + n - 1] != '\n')
	{
		_realloc(b);
		rack = rack + n;
	}
	if (n == 0)
	{
		if (fd > 2)
			close(fd);
		_checker("", envp, 'w');
		_setfree(FREE_ADDRESSES);
		_exit(0);
	}
	b->b_s[n + rack] = '\0';
	return (0);
}
/**
 * read_file - reads contents of files to buff_t
 * @b: buff_t
 * @envp: second param
 *
 * Return: 1 on file not exist, else 0
 */
int read_file(buff_t *b, list_e *envp)
{
	int fd, i;
	char *file, *fullfile;
	

	/* scan through buff_t and pull out file to read */
	i = b->bl_s;
        for ( ; is_w(b->b_s[i]); i++);

	if (!matchStrings(b->b_s + i, "simple_shell") || b->b_s[i] == '\0')
		return (0);
        for ( ;(!is_w(b->b_s[i]) && b->b_s[i] != '\0'); i++);

        for ( ;is_w(b->b_s[i]) && b->b_s[i] != '\0'; i++);

        if (b->b_s[i])
                fd = -1;

	else
	{
		file = b->b_s + i;
                for ( ;(!is_w(b->b_s[i]) && b->b_s[i] != '\0'); i++);

		b->b_s[i] = '\0';
		new_pth(&fullfile, file, "PWD", envp);
		fd = open(fullfile, O_RDONLY);
	}
	if (fd == -1)
	{
		_checker("", envp, 'w');
		_setfree(FREE_ADDRESSES);
		_exit(1);
	}
	get_line(b, fd, envp);
	close(fd);
	return (0);
}

