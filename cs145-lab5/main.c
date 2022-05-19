#include <stdio.h>
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
    char res[LCDSIZE] = {0};

    // initialize lcd
    lcd_init();
    avr_wait(SEC);
    lcd_clr();

    i = k = 0;

    while (1)
    {
        avr_wait(SEC / 2);

        k = get_key();
        if (k == 12)
        {
            lcd_clr();
            sprintf(res, "%.4f", calculator(i + 1, str));
            sprintf(str, "                ");
            i = 0;
        }

        else if (k)
            str[i++] = translate(k);

        display(str, res);
    }
}