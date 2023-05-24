#include "shell.h"
/**
 * print_error - error
 * @err: string to write to stderr
 */
void print_error(char *err)
{
        int size = _strlen(err);
	write(STDERR_FILENO, err, size);
}
