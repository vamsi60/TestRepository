#include <iostream>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

void *fun(void *);
int main()
{
	int ret;
	pthread_t tid;

	cout<<"Creating Thread\n";
	ret = pthread_create(&tid,NULL,fun,NULL);
	if (ret) {
		cout<<"THREAD CREATION FAILED\n";
		exit(-1);
	}
	pthread_exit(NULL);
}

void *fun(void *)
{
	cout<<"THREAD CREATED\n";
	pthread_exit(NULL);
}	
