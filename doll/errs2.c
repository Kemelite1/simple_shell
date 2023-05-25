#include "shell.h"
/**
 * cd_err - Creates an th message for shellby_cd errors.
 * @strs: An array of arguments passed to the command.
 *
 * Return: The th string.
 */
char *cd_err(char **strs)
{
	char *th, *chars;
	int g;

	chars = _itoa(hist);
	if (!chars)
		return (NULL);

	if (strs[0][0] == '-')
		strs[0][2] = '\0';
	g = _strlen(name) + _strlen(chars) + _strlen(strs[0]) + 24;
	th = malloc(sizeof(char) * (g + 1));
	if (!th)
	{
		free(chars);
		return (NULL);
	}

	_strcpy(th, name);
	_strcat(th, ": ");
	_strcat(th, chars);
	if (strs[0][0] == '-')
		_strcat(th, ": cd: Illegal option ");
	else
		_strcat(th, ": cd: can't cd to ");
	_strcat(th, strs[0]);
	_strcat(th, "\n");

	free(chars);
	return (th);
}

/**
 * unq_err - Creates an bll message for command not found failures.
 * @mss: An array of arguments passed to the command.
 *
 * Return: The bll string.
 */
char *unq_err(char **mss)
{
	char *bll, *chars;
	int hc;

	chars = _itoa(hist);
	if (!chars)
		return (NULL);

	hc = _strlen(name) + _strlen(chars) + _strlen(mss[0]) + 16;
	bll = malloc(sizeof(char) * (hc + 1));
	if (!bll)
	{
		free(chars);
		return (NULL);
	}

	_strcpy(bll, name);
	_strcat(bll, ": ");
	_strcat(bll, chars);
	_strcat(bll, ": ");
	_strcat(bll, mss[0]);
	_strcat(bll, ": not found\n");

	free(chars);
	return (bll);
}

/**
 * unq2_err - Creates an jg message for permission denied failures.
 * @dsa: An array of arguments passed to the command.
 *
 * Return: The jg string.
 */
char *unq2_err(char **dsa)
{
	char *jg, *ghd;
	int hjf;

	ghd = _itoa(hist);
	if (!ghd)
		return (NULL);

	hjf = _strlen(name) + _strlen(ghd) + _strlen(dsa[0]) + 24;
	jg = malloc(sizeof(char) * (hjf + 1));
	if (!jg)
	{
		free(ghd);
		return (NULL);
	}

	_strcpy(jg, name);
	_strcat(jg, ": ");
	_strcat(jg, ghd);
	_strcat(jg, ": ");
	_strcat(jg, dsa[0]);
	_strcat(jg, ": Permission denied\n");

	free(ghd);
	return (jg);
}