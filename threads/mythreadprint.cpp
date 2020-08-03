#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NTHREAD 5

using namespace std;

void *fun(void *);

pthread_attr_t tattr;

int main()
{
	int ret,j;
	long i;
	pthread_t tid[NTHREAD];
	ret = pthread_attr_init(&tattr);
	ret = pthread_attr_setschedpolicy(&tattr, SCHED_RR);
	for ( i = 1 ; i <= NTHREAD; i++) {
		pthread_create(&tid[i], &tattr, fun,(void *)i);
	}
	for ( j = 1; j <= NTHREAD; j++) {
		pthread_join(tid[j], NULL);
	}
	ret = pthread_attr_destroy(&tattr);
}

void *fun(void *ptr)
{
	long id=(long)ptr;
	cout<<"THREAD "<<id<<" CREATED\n";
}

