#include "shell.h"
int _putchar(char c)
{
	return (write(1, &c, 1));
}

void _puts(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str++);
	}
	// _putchar('\n');

}


void print_int(int num)
{
    char str[10];
    int index = 0;
    char temp;

    if (num < 0) {
        _putchar('-');
        num = -num;
    }
    
    do {
        str[index++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);
    str[index] = '\0';
    
    for (int i = 0, j = index - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
    
    for (int i = 0; str[i] != '\0'; i++) {
        _putchar(str[i]);
    }
}