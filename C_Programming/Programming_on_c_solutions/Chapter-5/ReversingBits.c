#include <stdio.h>
#include <stdint.h>

unsigned int ReverBits(unsigned int orig_num);

int main(void)
{
    printf("%u",ReverBits(25));

    return 1;
}

unsigned int ReverBits(unsigned int orig_num)
{
    char i,intsize=0;
    int j=1;
    unsigned int temp=0;

    while (j)
    {
        j <<= 1;
        intsize++;
    }
    for (i=0; i<32; i++)
    {
        temp |= ((orig_num>>i) & (1<<0)) << (intsize -i-1);
    }

    return temp;

}
