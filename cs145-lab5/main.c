#include <stdio.h>
#include <stdlib.h>
#include "avr.h"
#include "calculator.h"
#include "keypad.h"
#include "lcd.h"

#define LCDSIZE 17
#define SEC 1000

int main(void)
{
    char i, k;
    char str[LCDSIZE] = {0};

    // initialize lcd
    lcd_init();
    avr_wait(SEC);
    lcd_clr();

    while (1)
    {
        avr_wait(SEC / 2);

        k = get_key();
        if (k == 12)
            calculate(str);
        else if (k)
            str[i++] = (char)translate(k);

        char t[LCDSIZE] = "byebye";
        display(str, t);
    }
}