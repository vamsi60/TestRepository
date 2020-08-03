#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define COUNT_DONE 10
#define COUNT_HALT1 3
#define COUNT_HALT2 6

using namespace std;

void *fun1(void *);
void *fun2(void *);

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;

int count=0;
	
int main()
{
	pthread_t tid1,tid2;
	
	pthread_create(&tid1,NULL,fun1,NULL);
	pthread_create(&tid2,NULL,fun2,NULL);
	
	pthread_join( tid1, NULL);
	pthread_join( tid2,NULL);
	
}

void *fun1(void *ptr)
{
   cout<<"FUN1 EXECUTED\n";
   for(;;)
   {
      pthread_mutex_lock( &condition_mutex );
      while( count >= COUNT_HALT1 && count <= COUNT_HALT2 )
      {
         pthread_cond_wait( &condition_cond, &condition_mutex );
      }
      pthread_mutex_unlock( &condition_mutex );

      pthread_mutex_lock( &count_mutex );
      count++;
      printf("Counter value functionCount1: %d\n",count);
      pthread_mutex_unlock( &count_mutex );

      if(count >= COUNT_DONE) return(NULL);
   }

}

void *fun2(void *ptr)
{
   cout<<"FUN2 EXECUTED\n";
    for(;;)
    {
       pthread_mutex_lock( &condition_mutex );
       if( count < COUNT_HALT1 || count > COUNT_HALT2 )
       {
          pthread_cond_signal( &condition_cond );
       }
       pthread_mutex_unlock( &condition_mutex );

       pthread_mutex_lock( &count_mutex );
       count++;
       printf("Counter value functionCount2: %d\n",count);
       pthread_mutex_unlock( &count_mutex );

       if(count >= COUNT_DONE) return(NULL);
    }
}	
