#include <stdio.h>
#include <pthread.h>

#define NTHREADS 2

void *printoddeven(void *);

pthread_cond_t mycond[2];

pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

int oddeven = 1;

volatile int count=0;

int main()
{
    pthread_t tid[2]; int i;
    for(i=0; i<NTHREADS; i++)
    {
        pthread_cond_init(&mycond[i], NULL);
    }
    
    for(i=0; i<NTHREADS; i++)
    {
        pthread_create(&tid[i], NULL, printoddeven, (void *)&i);
    }
    
    for(i=0; i<NTHREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }
    return 0;
}

void *printoddeven(void *num)
{
    int tmp = *(int *)num;

    while(1)
    {
        pthread_mutex_lock(&mymutex);
        if(tmp != count)
        {
            pthread_cond_wait(&mycond[tmp], &mymutex);
        }
        
        printf("%d ", oddeven);
        oddeven++;
        
        if(count < NTHREADS-1)
            count++;
        else
            count=0;

        pthread_cond_signal(&mycond[count]);
        pthread_mutex_unlock(&mymutex);
    }
    return NULL;
}