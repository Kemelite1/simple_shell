#include "shell.h"
/**
 * compareStrings - compare strings
 * @string1: string 1
 * @string2: string 2
 * Description: Returns a match if either string reaches \0 or space
 *
 * Return: 1 if match, 0 if not match
 */
int compareStrings(char *string1, char *string2)
{
	int index;

	if (string1 == NULL || string2 == NULL)
		return (0);
	
	for (index = 0; string1[index] == string2[index]; index++)
	{
		if (string1[index] == '\0' || string2[index] == '\0')
			return (1);
		if (is_w(string1[index]) || is_w(string2[index]))
			return (1);
	}
	
	if (string1[index] == '\0' || string2[index] == '\0')
		return (1);
	if (is_w(string1[index]) || is_w(string2[index]))
		return (1);
	
	return 0;
}
/**
 * _isdigit - a function that checks for lowercase character
 * @c: single letter input
 * Return: 1 if int c is lowercase, 0 if otherwise
 */
int is_digit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
/**
 * _isalpha - a function that checks for alphabetic character
 * @c: single letter input
 * Return: 1 if c is a letter (lower or uppercase), 0 otherwise
 */
int is_alpha(int c)
{
	if (c >= 65 && c <= 122)
		return (1);
	else
		return (0);
}
/**
 * characterMatch - searches for a mathcing charater
 * @c: charater
 * @needles: string to search for matching char
 * Description: Returns true if char 'c' is a match for any character in
 *				needles, including \0. Therefore it is always a match
 *				if 'c' is \0. By design.
 * Return: 1 if match, 0 if no match.
 */
int characterMatch(char c, const char *needles)
{
	if (needles == NULL)
		return (0);

	do {
		if (c == *needles)
			return 1;
	} while (*needles++);

	return (0);
}
/**
 * matchStringsAndDelim - Find if strings match, w multiple delims to stop the match
 * @string1: string one
 * @string2: string two
 * @delimiter: symbol
 * 
 * Return: 1 if match, 0 if no match.
 */
int matchStringsAndDelim(char *string1, char *string2, char *delimiter)
{
    int index = 0;

    if (string1 == NULL || string2 == NULL || delimiter == NULL)
        return (0);

    while (string1[index] == string2[index])
    {
        if (characterMatch(string1[index], delimiter))
            return (1);
        index++;
    }

    if (characterMatch(string1[index], delimiter) || characterMatch(string2[index], delimiter))
        return (1);

    return (0);
}


