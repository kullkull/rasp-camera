#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "queue.h"
#include "service.h"

extern queue_t queue_irq;
extern pthread_mutex_t mutex;
extern pthread_cond_t cond;

static void perform_task(int pid, int req);


void* irq_service(void* arg)
{

THREAD_LOCK; //Block until all services are deployed..
printf("irq service is now on!\n");
THREAD_UNLOCK;

while(1)
{

	if( queue_irq.size > 0 )
	{
	queue_node *task = queue_dequeue(&queue_irq);
	perform_task(task->data->pid,task->data->req); 
	queue_free(task);
	}

}
}


static void perform_task(int pid, int req)
{

switch(pid)
{
	case 0:		//pid == 0  =>  network request
		switch(req)
		{
		//THREAD_LOCK; //Program may not work properly when preemtped by network service
		case 0:  _send_data_to_clnt( 0);break;
		case 1:  _send_data_to_clnt( 1);break;
		default: _send_data_to_clnt(-1);break;
		//THREAD_UNLOCK;
		}
		break;

	case 1:		//detect request

		break;

	case 2:		//cam request

		break;

	case 3:		//others...

		break;

}
}
