#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
static void mysignal(void);
void* mythread(void* arg);

int main(void)
{
pthread_t *fd;
int arg;
signal(SIGINT,(void*)mysignal);
pthread_create(fd,NULL,mythread,(void*)&arg);



while(1)
{
sleep(3);
kill(getpid(),2);


}


pthread_join(*fd,(void**)&arg);

}


void* mythread(void* arg)
{

signal(SIGINT,(void*)mysignal);

while(1)
{
sleep(1);
printf("\n\n");
}



}



static void mysignal(void)
{

printf("I received signal !!");
}
