#include "stdio.h"
#include "stdint.h"

float SquareRootNumb(float value);

int main(void)
{
    float value;

    while(1) {
    scanf("%f",&value);
    printf("\r\t%f\n",SquareRootNumb(value));
    }

    return 1;
}



float SquareRootNumb(float value)
{
    float SquareRoot_prev = 1,SquareRoot_new = 1;

    for (uint32_t i=0; i < 1000 ; i++) {

        SquareRoot_prev = SquareRoot_new;
        SquareRoot_new = (SquareRoot_new + (value/SquareRoot_new))/2;

        if (SquareRoot_prev == SquareRoot_new) { break; }

    }

    return SquareRoot_new;
}
