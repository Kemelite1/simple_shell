#include "shell.h"
/**
 * help_alias - builtin help printout for alias
 * Return: Always 0
 */
int help_alias(void)
{
	_puts("alias usage: alias [KEY][=VALUE]\n    Allows aliases to be set for");
	_puts(" quicker shell usage.\nAlias with no KEY VALUE prints a list of ");
	_puts("aliases.\nAlias with KEY prints the alias match for that key.\n");
	_puts("Alias with KEY VALUE sets or overwrites the KEY with new VALUE.\n");
	return (0);
}
/**
 * help_cd - builtin help printout for cd
 * Return: Always 0
 */
int help_cd(void)
{
	/* Maybe write more here, actualy help printout is a book */
	_puts("cd usage: cd DIR\n    Change the current directory to DIR.\n");
	return (EXIT_SUCCESS);
}
/**
 * help_env - builtin help printout for env
 * Return: Always 0
 */
int help_env(void)
{
	_puts("env usage: env\n    Prints out the current envirornment.\n");
	return (EXIT_SUCCESS);
}
/**
 * help_exit - builtin help printout for exit
 * Return: Always 0
 */
int help_exit(void)
{
	_puts("exit usage: exit N\n    Exit the shell.\n\n    ");
	_puts("Exits the shell with a status of N.  If N is omitted, ");
	_puts("the exit status\n    is that of the last command executed.\n");
	return (EXIT_SUCCESS);
}
/**
 * help_help - builtin help printout for help
 * Return: Always 0
 */
int help_help(void)
{
	_puts("help usage: help COMMAND\n    Display helpful info about builtins\n");
	return (0);
}
