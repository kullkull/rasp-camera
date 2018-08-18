#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
pthread_mutex_t mutex;
pthread_cond_t	cond;



void* thread1(void* arg)
{
int j =0;
pthread_mutex_lock(&mutex);
printf("aquired mutex lock thread");
fflush(stdout);
pthread_cond_signal(&cond);



while(j !=5)
{
printf("thread alive");
fflush(stdout);
sleep(1);
j++;
}
pthread_mutex_unlock(&mutex);


}



int main(void)
{
int i=0;
pthread_t pt;
pthread_mutex_init(&mutex,NULL);
pthread_cond_init(&cond,NULL);

pthread_mutex_lock(&mutex);
pthread_create(&pt,NULL,thread1,(void*)NULL);

while(1)
{
sleep(1);
printf("print from main\n");
i++;


if(i==5)
	pthread_cond_wait(&cond,&mutex);

}




return 0;
}
