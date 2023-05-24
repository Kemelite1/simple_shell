#include "shell.h"
/**
 * help_hist - builtin help printout for history
 * Return: Always EXIT_SUCCESS
 */
int help_hist(void)
{
	_puts("history usage: history\n    ");
	_puts("Display the history list with line numbers.\n");
	return (EXIT_SUCCESS);
}
/**
 * help_setenv - builtin help printout for setenv
 * Return: Always EXIT_SUCCESS
 */
int help_setenv(void)
{
	_puts("setenv usage: setenv VARIABLE VALUE\n    Initialize a new");
	_puts(" environment variable, or modify an existing one.\n");
	return (EXIT_SUCCESS);
}
/**
 * help_unsetenv - builtin help printout for unsetenv
 * Return: Always EXIT_SUCCESS
 */
int help_unsetenv(void)
{
	_puts("unsetenv usage: unsetenv VARIABLE:\n    ");
	_puts("Remove an envirornment variable.\n");
	return (EXIT_SUCCESS);
}
