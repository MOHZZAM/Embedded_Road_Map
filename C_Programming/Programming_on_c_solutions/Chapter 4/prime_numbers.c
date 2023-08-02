#include "stdio.h"
#include "stdint.h"


int main(void)
{
    for (int i = 1; i<=100; i++) {

        int j = 0;
        for ( j = i-1; j!=1; j--) {

            if (j != 0) {
            if (i%j == 0) { break;}
            }
        }

        if (( j == 1 ) || (j == -1)){ printf("\t%d",i);}
    }
    return 1;
}
