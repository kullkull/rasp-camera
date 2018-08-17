#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

pthread_cond_t cond;
pthread_mutex_t mutex;

void* thread(void *arg){

pthread_mutex_lock(&mutex);
printf("1");
fflush(stdout);
pthread_cond_wait(&cond,&mutex);
printf("3");
fflush(stdout);

}



void main(){

pthread_t thid;
pthread_mutex_init(&mutex, NULL);
pthread_cond_init(&cond,NULL);
pthread_create(&thid,NULL,thread,NULL);

printf("2");
fflush(stdout);
sleep(1);



pthread_cond_signal(&cond);
pthread_join(thid,NULL);


}
