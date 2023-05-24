#include "shell.h"
/**
 * strictStringMatch - See if two strings are matching
 * @string1: string 1
 * @string2: string 2
 * Description: Returns a match if both strings are the exactly the same
 *
 * Return: 1 if match, 0 if not match
 */
int strictStringMatch(const char *string1, const char *string2)
{
    int idx = 0;
    if (string1 == NULL || string2 == NULL)
        return (0);
    
    while (string1[idx] == string2[idx])
    {
        if (string1[idx] == '\0' || string2[idx] == '\0')
            return (1);
        idx++;
    }
    
    return (0);
}
/**
 * findSubstringIndex - finds the first occourance of the str
 * @text: string to search
 * @substring: string to find
 * Return: index to the beginning of the located substring
 */
int findSubstringIndex(const char *text, const char *substring)
{
    int index = 0;

    while (*text != '\0')
    {
        const char *textStart = text;
        const char *subStart = substring;

        while (*subStart == *text && *subStart != '\0' && *text != '\0')
        {
            text++;
            subStart++;
        }
        
        if (*subStart == '\0')
            return (index);
        
        text = textStart + 1;
        index++;
    }
    
    return (-1);
}
/**
 * findFirstCharacterIndex - new chars
 * @string: string
 * @character: Chars
 * Return: index of first char in s, else -1
 */
int findFirstCharacterIndex(const char *string, const char *characters)
{
    int index, charIndex;

    for (index = 0; string[index]; index++)
    {
        for (charIndex = 0; characters[charIndex]; charIndex++)
        {
            if (characters[charIndex] == string[index])
                return index;
        }
    }

    return -1;
}
/**
 * _strcmp - comparing strings
 * @s1 : var pointer
 * @s2 : pointer
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int a;

	for (a = 0; s1[a] != '\0' && s2[a] != '\0'; a++)
	{
		if (s1[a] != s2[a])
			return (s1[a] - s2[a]);
	}
	return (0);
}
