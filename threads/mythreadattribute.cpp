#include <iostream>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

void *fun(void *);

pthread_attr_t tattr;

int main()
{
	int ret;
	pthread_t tid;
	const char *mssg="THREAD";
	ret = pthread_attr_init(&tattr);
	ret = pthread_create(&tid, &tattr, fun,(void *)mssg);
	pthread_join(tid, NULL);
	ret = pthread_attr_destroy(&tattr);
}

void *fun(void *ptr)
{
	char *mssg=(char *)ptr;
	cout<<mssg<<" CREATED\n";
}

