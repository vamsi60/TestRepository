#include <iostream>
//#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int main()
{
	sem_t mysem;
	int value;
	sem_init(&mysem,0,0);
	sem_getvalue(&mysem,&value);
	cout<<"VALUE BEFORE LOCK IS "<<value<<endl;
	sem_wait(&mysem);
	sem_getvalue(&mysem,&value);
	cout<<"VALUE AFTER LOCK IS "<<value<<endl;
}
