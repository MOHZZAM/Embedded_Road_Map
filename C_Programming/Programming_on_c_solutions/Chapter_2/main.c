#include <stdio.h>

#include "increment.c"
#include "negate.c"

int main ()
{
    int value=1;
    while(1)
    {
        printf("\r \t%d \t%d ",negate(value),increment(value));
        Sleep(1000);
        value++;
    }

    return 1;
}
