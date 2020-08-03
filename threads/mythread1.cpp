#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <

using namespace std;

void *fun(void *);
int main()
{
	int ret;
	pthread_t tid1,tid2;
	const char *mssg1="THREAD 1";
	const char *mssg2="THREAD 2";
//	cout<<"Creating Thread1\n";
	ret = pthread_create(&tid1,NULL,fun,(void *)mssg1);
	if (ret) {
		cout<<"THREAD1 CREATION FAILED\n";
		exit(-1);
	}
//	pthread_join(tid1,NULL);
//	cout<<"Creating Thread2\n";
	ret = pthread_create(&tid2,NULL,fun,(void *)mssg2);
	if (ret) {
		cout<<"THREAD2 CREATION FAILED\n";
		exit(-1);
	}
	pthread_join( tid1,NULL);
	pthread_join( tid2,NULL);
//	cout<<"Thread 1 exited\n";
//	cout<<"Thread 2 exited\n";
	exit(0);
}

void *fun(void *ptr)
{
	char *mssg=(char *)ptr;
	cout<<"CREATED "<<mssg<<endl;
	pthread_exit(NULL);
}	
