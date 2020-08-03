#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

#define NTHREAD 5

using namespace std;

pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

void *fun(void *);

int count = 0;

int main()
{

	pthread_attr_t tattr;
	int newprio=50,j,ret;
	sched_param param[NTHTREAD];
	long i;		
	pthread_t tid[NTHREAD];
	ret = pthread_attr_init(&tattr);
	ret = pthread_attr_setschedpolicy(&tattr, SCHED_FIFO);
	param.sched_priority = newprio;
	ret = pthread_attr_setschedparam (&tattr, &param);

	for ( i = 1; i <= NTHREAD; i++) {
		ret = pthread_create(&tid[i],&tattr,fun,(void *)i);
	}

	for ( j = 1; j <= NTHREAD; j++) {
		pthread_join(tid[j], NULL);
	}

	pthread_attr_destroy(&tattr);
}

void *fun(void *ptr)
{
	pthread_mutex_lock(&mymutex);
	long id = (long)ptr;
	count++;
	cout<<"THREAD "<<id<<" CREATED & COUNT = "<<count<<" \n";
	pthread_mutex_unlock(&mymutex);
}

