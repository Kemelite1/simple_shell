#include "shell.h"
/**
 * arr_init - creates arr from linkedlist
 * @environ: environement
 * Return: a 2D arr containing strings contained in linked list
 */

char **arr_init(env_t *environ)
{
	char **arr;
	env_t *new;
	int ct, i, j;

        ct = 0;
        new = environ;
        while (new != NULL)
                ct++, new = new->next;
	// for (new = environ, ct = 0; new != NULL; new = new->next)
	// 	ct++;
	arr = malloc(sizeof(char *) * (ct + 1));

        new = environ;
        i = 0;
        while (new != NULL)
        {
              	j = _strlen(new->value);
		arr[i] = _malloc(sizeof(char) * (j + 1));
		_memset(arr[i], '\0', (j + 1));
		_memcpy(arr[i], new->value, j);
                i++, new = new->next;
        }
	// for (new = environ, i = 0; new != NULL; new = new->next, i++)
	// {
	// 	j = _strlen(new->value);
	// 	arr[i] = _malloc(sizeof(char) * (j + 1));
	// 	_memset(arr[i], '\0', (j + 1));
	// 	_memcpy(arr[i], new->value, j);
	// }
	arr[i] = NULL;
	return (arr);
}
char* intToString(int num, int mode)
{
    char* numStr;
    int currentIndex, exp, i, tempExp;

    numStr = _malloc(sizeof(char) * BUFSIZE);
    _memset(numStr, '\0', BUFSIZE);
    exp = 1000000000;
    currentIndex = 0;

    if (num != 0)
    {
        while ((num / exp) == 0)
            exp /= 10;
        
        tempExp = exp;

        while (tempExp < 1000 && mode == 2)
        {
            numStr[currentIndex++] = '0';
            tempExp *= 10;
        }

        while (exp >= 1)
        {
            numStr[currentIndex++] = (num / exp) + '0';
            num %= exp;
            exp /= 10;
        }
    }
    else
    {
        if (mode == 2)
        {
            for (i = 0; i < 4; i++)
                numStr[i] = '0';
        }
        else
            numStr[0] = '0';
    }

    return numStr;
}
// /**
//  * _itoa - interger to string converter
//  * @num: number to convert
//  * @mode: mode to determine how to deal with 0
//  * Return: a string for the number
//  */
// char *_itoa(int num, int mode)
// {
// 	char *num_str;
// 	int index, exp, i, temp_exp;

// 	num_str = malloc(sizeof(char) * BUFSIZE);
// 	memset(num_str, '\0', BUFSIZE);
// 	exp = 1000000000;
// 	index = 0;
// 	if (num != 0)
// 	{
// 		while ((num / exp) == 0)
// 			exp /= 10;
// 		temp_exp = exp;
// 		while (temp_exp < 1000 && mode == 2)
// 		{
// 			num_str[index++] = 0 + '0';
// 			temp_exp *= 10;
// 		}
// 		while (exp >= 1)
// 		{
// 			num_str[index++] = (num / exp) + '0';
// 			num %= exp;
// 			exp /= 10;
// 		}
// 	}
// 	else
// 	{
// 		if (mode == 2)
// 		{
// 			for (i = 0; i < 4; i++)
// 				num_str[i] = 0 + '0';
// 		}
// 		else
// 			num_str[0] = 0 + '0';
// 	}
// 	return (num_str);
// }
/**
 * is_w - chaecks for whitespace
 * @c: char to evalute.
 *
 * Return: 1 if whitespace, 0 if not
 */
int is_w(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
/**
 * input_finish - checks if end
 * @c: char to evaluate
 *
 * Return: 1 if end of command, 0 if not
 */
int input_finish(char c)
{
	if (c == '\0' || c == '\n' || c == '|' || c == '&' || c == ';' || c == '#')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
/**
 * end_inp - cut of
 * @cont: buffer
 */
void end_inp(char *cont)
{
	int i = 0;

	// for (i = 0; cont[i] != '\0'; i++);
    while (cont[i] != '\0')
        i++;
	i++;
	// for ( ; i > 0; i--)
    while (i > 0)
    {
		cont[i + 1] = cont[i];
        i--;
    }
        
	cont[i + 1] = cont[i];
	cont[i] = '\0';
}