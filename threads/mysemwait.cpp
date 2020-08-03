#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

void *fun(void *);

sem_t mymutex;
int count = 0;

int main()
{
	int ret; long i=1,j=2;
	cout<<"Initializing semaphore\n";
	sem_init(&mymutex,0,1);
	pthread_t tid1,tid2;
	cout<<"Creating threads\n";
	ret = pthread_create(&tid1,NULL,fun,(void *)i);
	ret = pthread_create(&tid2,NULL,fun,(void *)j);
	cout<<"Joining started\n";
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	cout<<"Destroying semaphore\n";
	sem_destroy(&mymutex);
}

void *fun(void *ptr)
{
	sem_wait(&mymutex);
	long id=(long)ptr;
	count++;
	cout<<"THREAD "<<id<<" CREATED & COUNT = "<<count<<"\n";
	sem_post(&mymutex);
}
