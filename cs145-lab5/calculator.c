#include "lcd.h"

#define SIZE 20

struct data_t
{
    int data[SIZE];
    int top;
};

struct symbo_t
{
    char symbol[SIZE];
    int top;
};

int calculate(const char *str[])
{
    return 0;
}

void display(const char *str1[], const char *str2[])
{
    lcd_pos(0, 0);
    lcd_puts2(str1);
    lcd_pos(1, 0);
    lcd_puts2(str2);
}

unsigned char translate(unsigned char k)
{
    switch (k)
    {
    case 1:
    case 2:
    case 3:
        k += 48;
        break;
    case 4:
        k += 39; // +
        break;
    case 5:
    case 6:
    case 7:
        k += 47;
        break;
    case 8:
        k += 37; // -
        break;
    case 9:
    case 10:
    case 11:
        k += 46;
        break;
    case 12: // calculate =
        break;
    case 13: // *
        k += 29;
        break;
    case 14:
        k += 34;
        break;
    case 15: // .
        k += 32;
        break;
    case 16: // /
        k += 30;
    }
    return k;
}