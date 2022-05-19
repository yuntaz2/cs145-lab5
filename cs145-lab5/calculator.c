#include <stdio.h>
#include "lcd.h"

#define SIZE 20

struct stack_t
{
    float data[SIZE];
    int top;
};

int calculate(const char *str)
{
    return 0;
}

void display(const char *str1, const char *str2)
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
void push(struct stack_t *stack, float v)
{
    stack->data[++stack->top] = v;
}

float pop(struct stack_t *stack)
{
    return stack->data[stack->top--];
}

float calculator(unsigned char argc, char *argv)
{
    struct stack_t nums;
    float currNum = 0.0;
    unsigned char prevOP = '+';

    nums.top = -1;
    unsigned char fp = 0;

    for (unsigned char i = 0; i < argc; ++i)
    {
        unsigned char k = argv[i];
        if ('0' <= k && k <= '9')
        {
            if (fp)
                currNum += 1.0 * (k - '0') / ((i - fp) * 10);
            else
                currNum = currNum * 10 + k - '0';
        }
        else if ('.' == k)
        {
            fp = i;
        }
        else
        {
            fp = 0;
            if ('+' == prevOP)
            {
                push(&nums, currNum);
                prevOP = k;
                currNum = 0;
            }
            else if ('-' == prevOP)
            {
                push(&nums, -currNum);
                prevOP = k;
                currNum = 0;
            }
            else if ('*' == prevOP)
            {
                float prevNum = pop(&nums);
                push(&nums, prevNum * currNum);
                prevOP = k;
                currNum = 0;
            }
            else if ('/' == prevOP)
            {
                float prevNum = pop(&nums);
                push(&nums, prevNum / currNum);
                prevOP = k;
                currNum = 0;
            }
        }
    }

    float res = 0;
    while (nums.top >= 0)
    {
        res += pop(&nums);
    }
    return res;
}