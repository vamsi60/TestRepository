#include <iostream>
#include <stdlib.h>
#include <pthread.h>

#define NTHREAD 5
using namespace std;

void *fun(void *);

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int count=1;
	
int main()
{
	int ret,i,j;
	pthread_t tid[NTHREAD];
	
	for ( i = 1; i <= NTHREAD; i++) {	
		cout<<"Creating thread: "<<i<<"\n";
		ret = pthread_create(&tid[i],NULL,fun,NULL);
		if (ret) {
			cout<<"THREAD 1 CREATION FAILED\n";
			exit(-1);
		}
	}
	for ( j = 1; j <= NTHREAD; j++) {	
		cout<<"Joining thread: "<<j<<"\n";
		pthread_join(tid[j],NULL);
	}
	cout<<"FINAL VALUE OF I : "<<count<<endl;
}
void *fun(void *ptr)
{
	cout<<"Thread Number : "<<pthread_self()<<endl;
	pthread_mutex_lock(&mutex1);
	count++;
	//cout<<"THREAD CREATED AND I = "<<i<<endl;
	pthread_mutex_unlock(&mutex1);
}
