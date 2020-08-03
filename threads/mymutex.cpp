#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TOTAL 3 
using namespace std;

void createthreads(int,int*);
void *fun(void *);

pthread_t tid;
pthread_mutex_t mutex1;
pthread_attr_t attr;
	
int main()
{
    int i,pri=10;
    int *ptr = new int;
    *ptr=1;
    for(i=0;i<TOTAL;i++)
    {
	createthreads(pri,ptr);
        sleep(1);
        pri = pri -2;
        ++*ptr;
    }
    sleep(5);     
}

void createthreads(int pri,int *ptr)
{
    cout << "CREATING\n";
    struct sched_param param;

   //pthread_mutex_lock(&mutex1);

    pthread_attr_init(&attr);

    pthread_attr_setschedpolicy (&attr, SCHED_FIFO);

    param.sched_priority = pri;

    pthread_attr_setschedparam (&attr, &param);

    pthread_create(&tid, &attr, fun,(void *)ptr);

   //pthread_mutex_unlock(&mutex1);
}

void *fun(void *id)
{
    pthread_mutex_lock(&mutex1);
    int *ptr = (int *)id;
    cout <<"THREAD : "<<*ptr<<endl;
    //*ptr++;
    pthread_mutex_unlock(&mutex1);

}
