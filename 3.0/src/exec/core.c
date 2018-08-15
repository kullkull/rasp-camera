#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include "service.h"
#include "network.h"

FILE *fp; //Debug Track
int NET_IRQ;
int DEC_IRQ;

int main(int argc, char *argv[])
{
pthread_t * network, *camera, *detection;
int net_ret,cam_ret,det_ret;
int __pid, __pipe[2];

if(pipe(__pipe) == -1)
	return -1;

	network	  = start_service(network_service,argv[1]);
	camera    = start_service(camera_service,(void*)__pipe[1]);
	detection = start_service(detect_service,(void*)__pipe[0]);

if(network == NULL || camera == NULL || detection == NULL)
	return -1;

_irq_handle();



pthread_join(*network,(void**)&net_ret);
pthread_join(*camera,(void**)&cam_ret);
pthread_join(*detection,(void**)&det_ret);

return 0;
}


static void _irq_handle(void)
{

while(1)
{
//If interrupt occurs... then

__pid = fork();

        if(__pid == 0 )
        {

        //work goes here

        }

}

}

