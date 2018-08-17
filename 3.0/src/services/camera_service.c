#include <unistd.h>
#include <string.h>



void* camera_service(void* arg)
{
int fd = *((int*)arg);

char sample[100]="camera data sending..";


while(1)
{
write(fd,sample,strlen(sample));
sleep(5);
}





}
