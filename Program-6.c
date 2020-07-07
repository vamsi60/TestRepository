/* Program to Find MostFrequentElement in an Array*/

#include <stdio.h>
#include <stdlib.h>

int mostfrequentelement(int *, int);
void main()
{
    int N, res;
    scanf("%d", &N);
    
    int *arr = (int *)malloc(N * sizeof(int));
    
    for(int i=0; i<N; i++)
    {
        scanf("%d", &arr[i]);
    }
    
    res = mostfrequentelement(arr,N);
    printf("Most Frequent Element is %d\n", res);
}

int mostfrequentelement(int arr[], int N)
{
    int maxcount=0, count, res;
    
    for(int i=0; i<N; i++)
    {
        count = 0;
        for(int j=0; j<N; j++)
        {
            if(arr[i] == arr[j]) {
                count++;
            }
        }
        if(maxcount == 0)
        {
            maxcount = count;
            res = arr[i];
        }
        if(count > maxcount)
        {
            maxcount = count;
            res = arr[i];
        }
    }
    return res;
}

