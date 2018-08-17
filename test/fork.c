#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


void call_fork(void);

int main(void)
{


call_fork();

return 0;

}



void call_fork(void)
{

int fd;
while(1)
{
sleep(2);
fd = fork();

if(fd ==0)
{
printf("child alive !!\n");

}
else
{
printf("mother alive\n");
return;

}



}




}
