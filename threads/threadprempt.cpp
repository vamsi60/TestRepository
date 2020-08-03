#include<iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_t tid,tid1;
pthread_mutex_t lock;
pthread_attr_t attr,attr1;
struct sched_param param,param1;
void *fun(void *);
void *fun1(void *);


int main()
{
int ret=0;

ret=pthread_attr_init(&attr);
if(ret != 0)
{
    cout<<"attr"<<endl;
}
ret=pthread_attr_setschedpolicy(&attr,SCHED_OTHER);
if(ret != 0)
{
    cout<<"schedpolicy thread1 failed"<<endl;
}

param.sched_priority = 0;
pthread_attr_setschedparam(&attr, &param);
pthread_create(&tid,&attr,fun,NULL);

pthread_attr_init(&attr1);
ret=pthread_attr_setschedpolicy(&attr,SCHED_FIFO);
if (ret != 0)
{
    cout<<"SCHED_FIFO Failed"<<endl;
}

param.sched_priority = 90;
pthread_attr_setschedparam(&attr1, &param1);
pthread_create(&tid1,&attr1,fun1,NULL);

pthread_join(tid,NULL);
pthread_join(tid1,NULL);
}

void *fun(void *input)
{
int i=0;
for (;i<1000000;i++)
{
cout <<"-";
}
}

void *fun1(void* test)
{
int j;
for(j=0;j<1000;j++)
{
cout<<"VAMSI";
}
}


