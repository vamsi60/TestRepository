#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 20

void main()
{
    char *str = (char *)malloc(MAX_LEN * sizeof(char));
    fgets(str,MAX_LEN,stdin);
    
    int count = 0;
    
    for(int i=0; str[i]!='\0'; i++)
    {
        count = 0;
        for(int j=0; str[j]!='\0'; j++)
        {
            if(str[i] == str[j])
                count++;
        }
        if(count == 1)
            printf("%c", str[i]);
    }
    
    free(str);
    
}