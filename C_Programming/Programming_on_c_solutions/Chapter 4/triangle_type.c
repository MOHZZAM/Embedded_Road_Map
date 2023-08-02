#include "stdio.h"
#include "stdint.h"


int main(void)
{
    int a,b,c;

    printf("\nEnter 1st number: ");
    scanf("%d",&a);
    printf("\nEnter 2nd number: ");
    scanf("%d",&b);
    printf("\nEnter 3rd number: ");
    scanf("%d",&c);

    if ((a == b) && (a == c)) {printf("\nEquilateral triangle");}
    else if ((a == b) || (a == c)) {printf("\nIsocales triangle");}
    else {printf("\nScalene triangle");}

    return 1;
}
