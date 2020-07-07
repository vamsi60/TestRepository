#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 20

void main()
{
    char *str = (char *)malloc(MAX_LEN * sizeof(char));
    char *substr = (char *)malloc(5 * sizeof(char));
    
    fgets(str,MAX_LEN,stdin);
    fgets(substr, 5, stdin);
    
    int count,i,k;
    int len = strlen(substr)-1;
    
    for(i=0; str[i]!='\0'; )
    {
        count = 0;
        while((str[i] != substr[0]) && (str[i] != '\0'))
            i++;
        
        for(k=0; k<len; i++,k++)
        {
            if(str[i] == substr[k])
                count++;
            else
                break;
        }
        if(count == len)
        {
            printf("String Found at Position %d\n", i-count+1);
            break;
        }
    }
    free(str);
    
}