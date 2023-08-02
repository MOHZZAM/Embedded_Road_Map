#include <stdio.h>
#include <stdint.h>

int store_bit_field( int original_value,int value_to_stor,unsigned starting_bit, unsigned ending_bit );


int main(void)
{
    printf("%d",store_bit_field(0xffff,0x123,15,4));
    return 1;
}

int store_bit_field( int original_value,int value_to_stor,unsigned starting_bit, unsigned ending_bit )
{
    int i,j=0;
    char bit_value=0;

    for ( i=ending_bit; i<=starting_bit; i++)
    {
        //Getting bit position value
        bit_value = ((value_to_stor >> j) & (1<<0));
        j++;

        //Masking bit position
        original_value &= ~(1<<i);

        //Storing value
        original_value |= (bit_value<<i);
    }

    return original_value;
}
