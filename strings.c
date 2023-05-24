#include "shell.h"
/**
 * rem_str - replace string
 * @str: pointer 
 * @n: position 
 * Description: override strings
 */
void rem_str(buff_t *str, int n)
{
	int i = 0;
        
	while (!(is_w(str->b_s[n + i]) || input_finish(str->b_s[n + i])))
	{
		str->b_s[n + i] = ' ';
		i++;
	}
}
/**
 * add_str - add a new string into a buff_t at a certan position
 * @b: pointer
 * @str: string
 * @position: position
 * Description: add a new str
 */
void add_str(buff_t *b, char *str, int position)
{
	unsigned int i, length;
	int j, s;

	rem_str(b, position);

	i = 0;
	while (is_w(b->b_s[position + i]) && (position + i) < b->sz)
		i++;
	s = i;
	if (s >  _strlen(str))
		; /* insert happens below */
	else
	{
		length = b->bl_s;
		length += _strlen(b->b_s + b->bl_s);
		length += _strlen(str);
		while (length > b->sz)
			_realloc(b);
		/* Find out how many chars remain in the string to move over */
		for (j = 0; b->b_s[j + position] != '\0'; j++)
			;
		/* Make room in buff_t by moving chars to the right */
		/* jth char at nth position + length of the string */
		/* - total open whitespace + 1 whitespace at end of cmd */
		for ( ; j >= 0; j--)
			b->b_s[j + position + _strlen(str) - i + 1] = b->b_s[j + position];
	}

        for (i = 0; str[i] != '\0'; i++)
        {
                b->b_s[position + i] = str[i], i++;
        }
}
