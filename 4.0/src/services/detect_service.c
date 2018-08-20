#include <unistd.h>
#include <string.h>
#include <stdio.h>

void* detect_service(void* arg){
/*

#	detect_service:
		1. the cam_service transmits data using pipe
		2. read function will be unblocked and data calculations will begin.
		3. if detects intrusion this service will call queue_enqueue function.
*/

int* fd = (int*)arg;
char buffer[100];




memset(buffer,0,sizeof(buffer));

while(1)
{
//printf("detect service %d\n",i++);
sleep(1);
//read(*fd,buffer,sizeof(buffer));
}


}
