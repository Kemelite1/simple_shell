#include "shell.h"
/**
 * rem_str - replace string
 * @str: pointer 
 * @n: position 
 * Description: override strings
 */
void rem_str(buffer *str, int n)
{
	int i;

        for (i = 0; !(is_w(str->buf[n + i]) || input_finish(str->buf[n + i])); i++)
        {
                str->buf[n + i] = ' ';
        }
        
	// while (!(is_w(str->buf[n + i]) || input_finish(str->buf[n + i])))
	// {
	// 	str->buf[n + i] = ' ';
	// 	i++;
	// }
}
/**
 * add_str - add a new string into a buffer at a certan position
 * @b: pointer
 * @str: string
 * @position: position
 * Description: add a new str
 */
void add_str(buffer *b, char *str, int position)
{
	int i, length, j;

	rem_str(b, position);

	i = 0;
        for (i = 0; is_w(b->buf[position + i]) && (position + i) < b->size; i++);
	// while (is_w(b->buf[position + i]) && (position + i) < b->size)
	// 	i++;
	// if (i >  _strlen(str))
	// 	; /* insert happens below */
	// else
        if (i <= _strlen(str))
	{
		length = b->bp;
		length += _strlen(b->buf + b->bp);
		length += _strlen(str);
		while (length > b->size)
			_realloc(b);
		/* Find out how many chars remain in the string to move over */
		for (j = 0; b->buf[j + position] != '\0'; j++)
			;
		/* Make room in buffer by moving chars to the right */
		/* jth char at nth position + length of the string */
		/* - total open whitespace + 1 whitespace at end of cmd */
		for ( ; j >= 0; j--)
			b->buf[j + position + _strlen(str) - i + 1] = b->buf[j + position];
	}
	// i = 0;
        for (i = 0; str[i] != '\0'; i++)
        {
                b->buf[position + i] = str[i], i++;
        }
        
	// while (str[i] != '\0')
	// 	b->buf[position + i] = str[i], i++;
}
