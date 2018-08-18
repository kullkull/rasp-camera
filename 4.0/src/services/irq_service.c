#include <pthread.h>
#include "queue.h"
#include "service.h"
extern queue_t queue_irq;

void* irq_service(void* arg)
{

//Wait for service to start ! 
//pthread_mutex_lock(mutex);

//Check there are interruptions...

while(1){

if(	queue_irq.size != 0	){
queue_node *task = queue_dequeue(&queue_irq);

switch(task->data->pid)
{
	case 0:		//network request
		switch(task->data->req)
		{
		case 0:  _send_data_to_clnt( 0);break;
		case 1:  _send_data_to_clnt( 1);break;
		default: _send_data_to_clnt(-1);break;
		}
		break;

	case 1:		//detect request

		break;

	case 2:		//cam request

		break;

	case 3:		//others...

		break;

}

queue_free(task);

}




}



}
