#include "shell.h"
/**
 * _strchr - Entry point
 * @s: input
 * @c: input
 * Return: Always 0 (Success)
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	for (; s[i] >= '\0'; i++)
	{
		if (s[i] == c)
			return (&s[i]);
	}
	return (0);
}
/**
 * _strlen - returns the length of a string
 * @s: string
 * Return: length
 */
int _strlen(char *s)
{
	int longi = 0;

	while (*s != '\0')
	{
		longi++;
		s++;
	}

	return (longi);
}
/**
 * _atoi - converts a string to an integer
 * @s: string to be converted
 *
 * Return: the int converted from the string
 */
int _atoi(char *s)
{
	int i, d, n, len, f, digit;

	i = 0;
	d = 0;
	n = 0;
	len = 0;
	f = 0;
	digit = 0;

	while (s[len] != '\0')
		len++;

	while (i < len && f == 0)
	{
		if (s[i] == '-')
			++d;

		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			if (d % 2)
				digit = -digit;
			n = n * 10 + digit;
			f = 1;
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			f = 0;
		}
		i++;
	}

	if (f == 0)
		return (0);

	return (n);
}
/**
 * duplicate - returns a copy to a new str
 * @str: string
 * Return: pointer to copy of string
 */

char *duplicate(char *str)
{
	char *cpy;
	unsigned int i, j;

	if (str == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++);
	i++;

	cpy = _malloc(i * sizeof(char));
        for (j = 0; j < i; j++)
		cpy[j] = str[j];

	return (cpy);
}
/**
 * matchStrings - See if two strings are matching
 * @string1: string 
 * @string2: string 
 * Description: Returns a match if either string reaches \0 or space
 *
 * Return: 1 if match, 0 if not match
 */
int matchStrings(const char *string1, const char *string2)
{
        int idx = 0;

        if (string1 == NULL || string2 == NULL)
                return 0;    
        while (string1[idx] == string2[idx])
        {
                if (string1[idx] == '\0' || string2[idx] == '\0')
                        return 1;
                idx++;
        }
    
        if (string1[idx] == '\0' || string2[idx] == '\0')
                return 1;
    
        return 0;
}
