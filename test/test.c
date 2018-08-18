#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define prt(a)	for(int i=0; i<5 ; i++){		\
			printf(#a); fflush(stdout);	\
			sleep(1);			\
			}

pthread_mutex_t mutex;
pthread_cond_t cond;


void* thread1(void* arg)
{
pthread_mutex_lock(&mutex);
prt(2);
pthread_cond_signal(&cond);
prt(4);
prt(9);
pthread_mutex_unlock(&mutex);

}


int main(void)
{
int a;
pthread_t pt;

pthread_mutex_init(&mutex,NULL);
pthread_cond_init(&cond,NULL);

pthread_mutex_lock(&mutex);
pthread_create(&pt,NULL,thread1,(void*)&a);
prt(1);
pthread_cond_wait(&cond,&mutex);
prt(3);

pthread_mutex_unlock(&mutex);
pthread_join(pt,(void**)&a);



}
