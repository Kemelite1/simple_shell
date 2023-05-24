#include "shell.h"
/**
 * _del_nm - removes name
 * @environ: environement
 * @tb_rm: search
 * @size: size
 * Return: a string containing the path
 */
char *_del_nm(list_e *environ, char *tb_rm, int size)
{
	char *cur_dir;
	list_e *new;

	cur_dir = _malloc(sizeof(char) * size);
	_memset(cur_dir, '\0', size);
	new = environ;
	for (; ; new = new->next)
	{
		if (compareStrings(new->hold, tb_rm))
		{
			_strcpy(cur_dir, new->hold);
			break;
		}
		else if (new->next == NULL)
		{
			_free(cur_dir);
			return (NULL);
		}
	}
	while (*cur_dir != '=')
		cur_dir++;
	cur_dir++;
	return (cur_dir);
}
/**
 * _ret_val - retrives a hold from the environment list
 * @environ: the env list
 * @key: key
 * Return: a pointer
 */
char *_ret_val(list_e *environ, char *key)
{
	char *new_val;

	while (1)
	{
		if (compareStrings(environ->hold, key))
		{
			new_val = environ->hold;
			break;
		}
		else if (environ->next == NULL)
			return (NULL);
		environ = environ->next;
	}
	while (*new_val++ != '=');

	return (new_val);
}
/**
 * _rem_pth - remove symbols from pwd
 * @environ: environement
 * @pth: pth
 * @size: size
 */
char *_rem_pth(char **arr, list_e *environ, char *pth, int size)
{
	int i, sym_num, identifyer;
	char *curdir, *new_path;

	new_path = _malloc(sizeof(char) * size);
	_memset(new_path, '\0', size);
	_strcpy(new_path, pth);
        i = 0;
        sym_num = 0;
        while (new_path[i] != '\0')
        {
                if (new_path[i] == '/')
                        sym_num++;
                i++;
        }

	curdir = arr[1];
	if (_strcmp(curdir, ".") == 0)
		new_path = _del_nm(environ, "PWD=", size);
	else if (_strcmp(curdir, "~") == 0)
		new_path = _del_nm(environ, "HOME=", size);
	else if (_strcmp(curdir, "..") == 0)
	{
                identifyer = 0;
                i = 0;
                while (identifyer < sym_num - 1)
                {
                        if (new_path[i] == '/')
				identifyer++;
                        i++;;
                }
                
		new_path[i - 1] = '\0';
	}
	else if (_strcmp(curdir, "-") == 0)
		new_path = _del_nm(environ, "OLDPWD=", size);
	return (new_path);
}
/**
 * new_pth - new pth for tghe bfile
 * @pth: pth to create
 * @file: file
 * @character: character
 * @environment: environement
 * Return: the pth str
 */
char *new_pth(char **pth, char *file, char *character, list_e *environ)
{
	char *hold;

	if (_strstr(character, "/"))
	{
		*pth = file;
		return (file);
	}

	hold = _ret_val(environ, character);
	*pth = _malloc(sizeof(char) * (_strlen(hold) + _strlen(file) + 2));
	_memcpy(*pth, hold, _strlen(hold) + 1);
	strcat(*pth, "/");
	strcat(*pth, file);
	return (*pth);
}
/**
 * env_shell - environment builtin
 * @arr: args
 * @environ: environment
 * Return: 0 if success.
 */
int env_shell(char **arr, list_e *environ)
{
	int count;

	if (arr[1] == NULL)
	{
		env_shw(environ);
		return (EXIT_SUCCESS);
	}
	
        count = 1;
        while (arr[count] != NULL)
        {
		arr[count - 1] = arr[count];
                count++;
        }

	arr[count - 1] = arr[count];
	return (EXIT_FAILURE);
}
