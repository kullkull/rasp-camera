#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "service.h"
#include "network.h"

FILE *fp; //Debug Track
pthread_cond_t cond;
pthread_mutex_t mutex;

static void net_irq_handle(void);

int NET_IRQ=0;
int DEC_IRQ=0;


int main(int argc, char *argv[])
{
if(argc !=2)
	return -1;

pthread_t * network, *camera, *detection;
int net_ret,cam_ret,det_ret;
int  __pipe[2];

pthread_mutex_init(&mutex, NULL);
pthread_cond_init(&cond,NULL);

if(pipe(__pipe) == -1)
	return -1;
	
pthread_mutex_lock(&mutex);
	network	  = start_service(network_service,argv[1]);
	camera    = start_service(camera_service,(void*)&__pipe[1]);
	detection = start_service(detect_service,(void*)&__pipe[0]);
	//camera sends data to detection thread

if(network == NULL || camera == NULL || detection == NULL)
	return -2;
//if interrup occurs then ... call _irq_handle()
//_irq_handle();

while(1)
{
	
pthread_cond_wait(&cond,&mutex);
//pthread_mutex_unlock(&mutex);

	if(NET_IRQ != 0 )
	{	
		net_irq_handle();
		NET_IRQ = 0;
	}

}

pthread_join(*network,(void**)&net_ret);
pthread_join(*camera,(void**)&cam_ret);
pthread_join(*detection,(void**)&det_ret);

return 0;
}



static void net_irq_handle(void)
{
int __pid = fork();

	if(__pid == 0 )
	{
		if(NET_IRQ == 1)
			_send_data_to_clnt(0);
		
		else
			_send_data_to_clnt(1);
	
	
        exit(0);
 	}



}


