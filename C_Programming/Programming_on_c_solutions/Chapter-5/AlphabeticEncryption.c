#include <stdio.h>
#include <stdint.h>

void AlphEncryp(const char * input, char *output);

int main(void)
{
    char msg[100];
    AlphEncryp("AaBbZzMm",msg);
    printf("%s",msg);

    return 1;
}

void AlphEncryp(const char * input, char *output)
{
    int  i,temp=0;
    for (i=0; input[i] != '\0'; i++)
    {
        if ((input[i] >= 65)&&(input[i] <= 90))
        {
            if ((input[i]-13) >= 65)
                output[i] = input[i] - 13;
            else
                output[i] = input[i] + 13;
        }
        else if ((input[i] >= 97)&&(input[i] <= 122))
        {
            if ((input[i]-13) >= 97)
                output[i] = input[i] - 13;
            else
                output[i] = input[i] + 13;
        }
        else
        {
            output[i] = input[i];
        }
    }

    output[i] = '\0';
}
