#include "shell.h"
/**
 * pth_err - Creates an er message for shellby_env errors.
 * @arr: An array of arguments passed to the command.
 *
 * Return: The er string.
 */
char *pth_err(char **arr)
{
	char *gbage, *chars;
	int l;

	chars = _itoa(hist);
	if (!chars)
		return (NULL);

	arr--;
	l = _strlen(name) + _strlen(chars) + _strlen(arr[0]) + 45;
	gbage = malloc(sizeof(char) * (l + 1));
	if (!gbage)
	{
		free(chars);
		return (NULL);
	}

	_strcpy(gbage, name);
	_strcat(gbage, ": ");
	_strcat(gbage, chars);
	_strcat(gbage, ": ");
	_strcat(gbage, arr[0]);
	_strcat(gbage, ": Unable to add/remove from environment\n");

	free(chars);
	return (gbage);
}
/**
 * exit_err - Creates an er message for shellby_exit errors.
 * @arr: An array of arguments passed to the command.
 *
 * Return: The er string.
 */
char *exit_err(char **arr)
{
	char *mist, *strings;
	int l;

	strings = _itoa(hist);
	if (!strings)
		return (NULL);

	l = _strlen(name) + _strlen(strings) + _strlen(arr[0]) + 27;
	mist = malloc(sizeof(char) * (l + 1));
	if (!mist)
	{
		free(strings);
		return (NULL);
	}

	_strcpy(mist, name);
	_strcat(mist, ": ");
	_strcat(mist, strings);
	_strcat(mist, ": exit: Illegal number: ");
	_strcat(mist, arr[0]);
	_strcat(mist, "\n");

	free(strings);
	return (mist);
}
/**
 * main_err - Creates an er message for shellby_alias errors.
 * @arr: An array of arguments passed to the command.
 *
 * Return: The er string.
 */
char *main_err(char **arr)
{
	char *cst;
	int l;

	l = _strlen(name) + _strlen(arr[0]) + 13;
	cst = malloc(sizeof(char) * (l + 1));
	if (!cst)
		return (NULL);

	_strcpy(cst, "alias: ");
	_strcat(cst, arr[0]);
	_strcat(cst, " not found\n");

	return (cst);
}
/**
 * type_err - Creates an er message for syntax errors.
 * @arr: An array of arguments passed to the command.
 *
 * Return: The er string.
 */
char *type_err(char **arr)
{
	char *trsh, *s;
	int len;

	s = _itoa(hist);
	if (!s)
		return (NULL);

	len = _strlen(name) + _strlen(s) + _strlen(arr[0]) + 33;
	trsh = malloc(sizeof(char) * (len + 1));
	if (!trsh)
	{
		free(s);
		return (NULL);
	}

	_strcpy(trsh, name);
	_strcat(trsh, ": ");
	_strcat(trsh, s);
	_strcat(trsh, ": Syntax trsh: \"");
	_strcat(trsh, arr[0]);
	_strcat(trsh, "\" unexpected\n");

	free(s);
	return (trsh);
}
