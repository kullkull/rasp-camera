#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "service.h"
#include "network.h"
#include "queue.h"

FILE *fp; //Debug Track
pthread_cond_t cond;
pthread_mutex_t mutex;

queue_t queue_irq; //irq handler

//static void net_irq_handle(void);

//int NET_IRQ=0;
//int DEC_IRQ=0;

int main(int argc, char *argv[])
{
if(argc !=2)
	return -1;

pthread_t * network, *camera, *detection, *irq;
int ret[4];
int  __pipe[2];


queue_create(&queue_irq);


pthread_mutex_init(&mutex, NULL);
pthread_cond_init(&cond,NULL);

if(pipe(__pipe) == -1)
	return -1;

//pthread_mutex_lock(&mutex);//Lock

	network	  = start_service(network_service,argv[1]);
	camera    = start_service(camera_service,(void*)&__pipe[1]);
	detection = start_service(detect_service,(void*)&__pipe[0]);
	irq	  = start_service(irq_service,(void*)NULL);

	//camera sends data to detection thread

if(network == NULL || camera == NULL || detection == NULL || irq ==NULL)
	return -2;


while(1){

queue_print(&queue_irq);
sleep(1);
}




pthread_join(*network,(void**)&ret[0]);
pthread_join(*camera,(void**)&ret[1]);
pthread_join(*detection,(void**)&ret[2]);
pthread_join(*irq,(void**)&ret[3]);
printf("Service all ended with service time of *** seconds");

}

//if interrup occurs then ... call _irq_handle()
//_irq_handle();
/*
while(1)
{
pthread_cond_wait(&cond,&mutex); //Unlock 1 7
printf("%d\n",NET_IRQ);
net_irq_handle();//8		
NET_IRQ = 0;//9
pthread_cond_signal(&cond); //11

}

pthread_join(*network,(void**)&net_ret);
pthread_join(*camera,(void**)&cam_ret);
pthread_join(*detection,(void**)&det_ret);

return 0;
}



*/





/*



static void net_irq_handle(void)
{
int __pid = fork();

	if(__pid == 0 )
	{
	_send_data_to_clnt(NET_IRQ);

        exit(0);
 	}



}


*/
