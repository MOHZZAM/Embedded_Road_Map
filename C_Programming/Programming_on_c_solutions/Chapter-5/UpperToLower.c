#include <stdio.h>
#include <stdint.h>

void UppToLow(const char * input, char *output);

int main(void)
{
    char msg[100];
    UppToLow("HellO123hJKHHHHHoHHHKKKkkkk",msg);
    printf("%s",msg);

    return 1;
}

void UppToLow(const char * input, char *output)
{
    int  i;
    for (i=0; input[i] != '\0'; i++)
    {
        if ((input[i] >= 65) && (input[i] <= 90))
        {
            output[i] = input[i] + 32;
        }
        else
        {
            output[i] = input[i];
        }
    }

    output[i] = '\0';
}
