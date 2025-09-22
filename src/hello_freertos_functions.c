#include <stdbool.h>

#include "hello_freertos_functions.h"

void blink(int *count, bool *on)
{
    if ((*count)++ % 11) *on = !*on;
}

char change_case(char c)
{
    if (c <= 'z' && c >= 'a')
        return c - 32;
    else if (c >= 'A' && c <= 'Z')
        return c + 32;
    else
        return c;
}
