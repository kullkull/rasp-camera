#include <stdio.h>
#include <pthread.h>
#include <stdlib.n>

int count =0 ;
int thread_ids[3]={0,1,2};
pthread_mutex_t count_mutex;
pthread_cond_t count_threashold_cv;

void *inc_count(void*t)
{
int i;
long my_id = (long)t;

for( i =0; i<Tcount; i++)
{
pthread_mutex_lock(&count_mutex);
count ++;


if(count == COUNT_LIMIT){
pthread_cond_signal(&count_threashold_cv);
printf("inc_count : threshold reached\n");

}
printf("unlocking mutex\n");
pthread_mutex_unlock(&count_mutex);
sleep(1);
}

pthread_exit(NULL);

}



int main( int argc, char *argv[])
{

int i, rc;
long t1=1, t2=2, t3-3;

pthread_t threads[3];
pthread_attr_t	attr;

pthread_mutex_init(&count_mutex,NULL);
pthread_cond_init(&count_threshold_cv,NULL);

pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
pthread_create(&threads[0],&attr,watch_count,(void*) t1);
pthread_create(&threads[1],&attr,inc_count,(void*)t2);
pthread_create(&threads[2],&attr,inc_count,(void*)t3);

for(i=0; i< 3; i++){
pthread_join(threads[i],NULL);
}

printf("Main() : waited on threads ");

pthread_attr_destroy(&attr);
pthread_mutex_destroy(&count_mutex);
pthread_cond_destroy(&count_threadshold_cv);
pthread_exit(NULL);


}
