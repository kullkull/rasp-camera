#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "service.h"
#include "network.h"
#include "queue.h"

FILE *fp; //Debug
pthread_cond_t cond; //conditions to wake thread
pthread_mutex_t mutex;

queue_t queue_irq; //irq handler queue
int current_status = 0; //0 ok 1 detected

int main(int argc, char *argv[])
{

pthread_t  network, camera, detection, irq;
int ret[4], __pipe[2];

queue_create(&queue_irq);
pthread_mutex_init(&mutex, NULL);
pthread_cond_init(&cond,NULL);

THREAD_LOCK;//------------------------------------------------------------------------------

if(pipe(__pipe) == -1)
	return -1;

	if(pthread_create(&network,NULL,network_service,(void*)argv[1]))	//at fails it returns > 0
		return -2;
	if(pthread_create(&network,NULL,camera_service,(void*)&__pipe[1]))
		return -3;
	if(pthread_create(&network,NULL,detect_service,(void*)&__pipe[0]))
		return -4;
	if(pthread_create(&network,NULL,irq_service,(void*)NULL))
		return -5;

printf("All services are on\n");
THREAD_UNLOCK;//----------------------------------------------------------------------------


pthread_join(network,(void**)&ret[0]);
pthread_join(camera,(void**)&ret[1]);
pthread_join(detection,(void**)&ret[2]);
pthread_join(irq,(void**)&ret[3]);

}

