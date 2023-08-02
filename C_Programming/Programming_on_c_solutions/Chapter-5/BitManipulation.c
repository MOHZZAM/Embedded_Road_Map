#include <stdio.h>
#include <stdint.h>


void set_bit( char bit_array[],unsigned bit_number );
void clear_bit( char bit_array[], unsigned bit_number );
void assign_bit( char bit_array[], unsigned bit_number, int value );
int test_bit( char bit_array[],unsigned bit_numlber );

int main(void)
{
    char msg[100] = "01110110";


    printf("%d",test_bit(msg,4));

    return 1;
}


void set_bit( char bit_array[],unsigned bit_number )
{
    bit_array[bit_number] = 49;
}
void clear_bit( char bit_array[], unsigned bit_number )
{
    bit_array[bit_number] = 48;
}
void assign_bit( char bit_array[], unsigned bit_number, int value )
{
    bit_array[bit_number] = value + 48;
}
int test_bit( char bit_array[],unsigned bit_number )
{
    if (bit_array[bit_number] == '0')
    {
        return 0;
    }
    return 1;
}
