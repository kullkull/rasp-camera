#include <unistd.h>
#include <string.h>
#include <stdio.h>
void* detect_service(void* arg)
{
int fd = *((int*)arg);
char buffer[100];
memset(buffer,0,sizeof(buffer));

while(1)
{
read(fd,buffer,sizeof(buffer));
//printf("received string ... >> %s\n",buffer);

}


}
