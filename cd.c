#include "shell.h"

/**
 * func_cd - gets new directory to swith cto
 * @new_dir: directory to change to
 * @environ: environement
 * @size: size of the buffer
 * Return: returns pth
 */

char *func_cd(char **new_dir, list_e *environ, int size)
{
	char *pt;
	int i, j;

	pt = _malloc(sizeof(char) * size);
	_memset(pt, '\0', size);
	i = j = 1;
	if (new_dir[1] != NULL)
	{
		i = _strcmp(new_dir[1], "~");
		j = _strcmp(new_dir[1], "-");
	}
	if (new_dir[1] == NULL || i == 0)
	{
		pt = _ret_val(environ, "HOME=");
		if (pt == NULL)
		{
			_puts("Error: variable Home not found\n");
			return (NULL);
		}
	}
	else if (new_dir[1] != NULL && j == 0)
	{
		pt = _ret_val(environ, "OLDPWD=");
		if (pt == NULL)
		{
			_puts("Error: variable OLDPWD not found\n");
			return (NULL);
		}
		_puts(pt), _puts("\n");
	}
	else if (new_dir[1][0] == '/')
		pt = new_dir[1];
	else
	{
		getcwd(pt, size);
		_strcat(pt, "/");
		_strcat(pt, new_dir[1]);
	}
	return (pt);
}
/**
 * cd_shell - builtin command
 * @arr: arr
 * @environ: environement
 * @size: size
 * Return: 0 on success and 1 on failure
 */
int cd_shell(char **arr, list_e *environ, int size)
{
	char *pth, *contain, *cur_dir;
	int l;

	contain = _malloc(sizeof(char) * size), _memset(contain, '\0', size);
	cur_dir = _malloc(sizeof(char) * size), _memset(cur_dir, '\0', size);
	getcwd(cur_dir, size);
	pth = func_cd(arr, environ, size);
	if (pth == NULL)
		return (2);
	l = chdir(pth);
	if (l < 0)
	{
		/*write(0, "Error: no such file or directory\n", 33);*/
		return (2);
	}
	else
	{
		getcwd(contain, size);
		cng_env(environ, "OLDPWD=", cur_dir, size);
		cng_env(environ, "PWD=", contain, size);
	}
	return (EXIT_SUCCESS);
}
