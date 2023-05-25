#include "shell.h"

/**
 * help_sh - Displays information about shellby builtin commands.
 * @arr: An array of arguments.
 * @ace: A pointer to the beginning of arr.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int help_sh(char **arr, char __attribute__((__unused__)) **ace)
{
	if (!arr[0])
		help_all();
	else if (_strcmp(arr[0], "alias") == 0)
		help_alias();
	else if (_strcmp(arr[0], "cd") == 0)
		help_cd();
	else if (_strcmp(arr[0], "exit") == 0)
		help_exit();
	else if (_strcmp(arr[0], "env") == 0)
		help_env();
	else if (_strcmp(arr[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(arr[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(arr[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}

/**
 * built_main - Matches a command with a corresponding
 *               shellby builtin function.
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*built_main(char *command))(char **arr, char **ace)
{
	builtin_t table[] = {
		{ "exit", shellby_exit },
		{ "env", shellby_env },
		{ "setenv", shellby_setenv },
		{ "unsetenv", shellby_unsetenv },
		{ "cd", cd_sh },
		{ "alias", shellby_alias },
		{ "help", help_sh },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; table[i].name; i++)
	{
		if (_strcmp(table[i].name, command) == 0)
			break;
	}
	return (table[i].f);
}
/**
 * cd_sh - Changes the current directory of the shellby process.
 * @arr: An array of arguments.
 * @ace: A double pointer to the beginning of arr.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int cd_sh(char **arr, char __attribute__((__unused__)) **ace)
{
	char **cur, *nl = "\n";
	char *pre_dir = NULL, *pwd = NULL;
	struct stat dir;

	pre_dir = getcwd(pre_dir, 0);
	if (!pre_dir)
		return (-1);

	if (arr[0])
	{
		if (*(arr[0]) == '-' || _strcmp(arr[0], "--") == 0)
		{
			if ((arr[0][1] == '-' && arr[0][2] == '\0') ||
					arr[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(pre_dir);
				return (create_error(arr, 2));
			}
		}
		else
		{
			if (stat(arr[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(arr[0]);
			else
			{
				free(pre_dir);
				return (create_error(arr, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	cur = malloc(sizeof(char *) * 2);
	if (!cur)
		return (-1);

	cur[0] = "OLDPWD";
	cur[1] = pre_dir;
	if (shellby_setenv(cur, cur) == -1)
		return (-1);

	cur[0] = "PWD";
	cur[1] = pwd;
	if (shellby_setenv(cur, cur) == -1)
		return (-1);
	if (arr[0] && arr[0][0] == '-' && arr[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, nl, 1);
	}
	free(pre_dir);
	free(pwd);
	free(cur);
	return (0);
}
/**
 * shellby_exit - Causes normal process termination
 *                for the shellby shell.
 * @arr: An array of arguments containing the exit value.
 * @ace: A double pointer to the beginning of arr.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int exit_sh(char **arr, char **ace)
{
	int i, li = 10;
	unsigned int digit = 0, full = 1 << (sizeof(int) * 8 - 1);

	if (arr[0])
	{
		if (arr[0][0] == '+')
		{
			i = 1;
			li++;
		}
		for (; arr[0][i]; i++)
		{
			if (i <= li && arr[0][i] >= '0' && arr[0][i] <= '9')
				digit = (digit * 10) + (arr[0][i] - '0');
			else
				return (create_error(--arr, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (digit > full - 1)
		return (create_error(--arr, 2));
	arr -= 1;
	free_args(arr, ace);
	free_env();
	free_alias_list(aliases);
	exit(digit);
}