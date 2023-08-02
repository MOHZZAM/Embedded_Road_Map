#include "stdio.h"
#include "stdint.h"

void copy_n( char dst[], char src[], int n );

int main(void)
{
    char a[10];
    char b[10] = "Hello";
    copy_n(a,b,9);
    printf("%s",a);
    return 1;
}

void copy_n( char dst[], char src[], int n )
{
    char flag=1;
    for (int i=0; i<n; i++) {
        if (src[i] == '\0') {
            flag = 0;
        }

        if (flag)
        {
            dst[i] = src[i];
        }
        else {
            dst[i] = '\0';
        }

    }
}
