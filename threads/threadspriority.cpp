#include <iostream>
#include <pthread.h>
#include <stdlib.h>

#define COUNT 2

void *display(void *);

using namespace std;

int main()
{
    pthread_t th[COUNT];
    pthread_attr_t attr1[COUNT];
    struct sched_param sp[COUNT];

    int i,rt;char *message="ONE"; char *message1="TWO";
    for (i=0;i<COUNT;i++)
	pthread_attr_init(&attr1[i]);

    for (i=0;i<COUNT;i++)
    {
	cout << "DISPLAYING ATTRIBUTES FOR THREAD : " << (i+1) << endl;

	rt = pthread_attr_getdetachstate(&attr1[i],&rt);
	cout << ( rt == PTHREAD_CREATE_JOINABLE ? "PTHREAD_CREATE_JOINABLE" : "PTHREAD_CREATE_DETACHSTATE" ) << endl;

	rt = pthread_attr_getscope(&attr1[i],&rt);
	cout << ( rt == PTHREAD_SCOPE_PROCESS ? "PTHREAD_SCOPE_PROCESS" : "PTHREAD_SCOPE_SYSTEM" ) << endl;

	rt = pthread_attr_getinheritsched(&attr1[i],&rt);
	cout << (rt == PTHREAD_INHERIT_SCHED ? "PTHREAD_INHERIT_SCHED" : "PTHREAD_EXPLICIT_SCHED" ) << endl;

	rt = pthread_attr_getschedpolicy(&attr1[i],&rt);
	cout << ( rt == SCHED_OTHER ? "SCHED_OTHER" : "SCHED_FIFO" ) << endl;

	rt = pthread_attr_getschedparam(&attr1[i],&sp[i]);
	cout << "PRIORITY : " << sp[i].sched_priority << endl;
    }

    //for (i=0;i<COUNT;i++)
    	//pthread_create(&th[i],&attr1[i],display,(void *)message);
    	pthread_create(&th[0],&attr1[0],display,(void *)message);
    	pthread_create(&th[1],&attr1[1],display,(void *)message1);

    for (i=0;i<COUNT;i++)
	pthread_join(th[i],NULL);

    exit(0);
}

void *display(void *msg)
{
    char *ptr;
    ptr = (char *)msg;
    cout << ptr <<endl;
}
