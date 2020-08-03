#include <iostream>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

void *fun1(void *);
void *fun2(void *);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
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
	pthread_mutex_lock(&mutex1);
	count++;
	cout<<"FUN1 CREATED AND COUNT = "<<count<<endl;
	pthread_mutex_unlock(&mutex1);
}

void *fun2(void *ptr)
{
	pthread_mutex_lock(&mutex1);
	count++;
	cout<<" FUN2 CREATED AND COUNT = "<<count<<endl;
	pthread_mutex_unlock(&mutex1);
}
