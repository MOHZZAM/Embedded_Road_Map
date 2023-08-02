#include <stdio.h>
#include <stdint.h>

char *find_char( char const *source,char const *chars );


int main(void)
{
    const char msg1[100] = "ABCDEFG";
    const char msg2[100] = "XYZ";
    char *verify;
    verify = find_char(msg1,msg2);
    if (verify != NULL)
        printf("%c %d",*(verify),verify);
    else
        printf("NULL");
    return 1;
}

char *find_char( char const *source,char const *chars )
{
    const char* cptr;
    if ((source != NULL) && (chars != NULL))
    {
        while (*source != '\0')
        {
            for ( cptr=chars; *cptr != '\0'; cptr++)
            {
                if (*cptr == *source)
                {
                    return source;
                }
            }
            source++;
        }
    }

    return NULL;
}
