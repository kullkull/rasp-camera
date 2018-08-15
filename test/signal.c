#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sig_handler(int signo);

int main(void)
{

int i = 0;
signal(SIGINT,(void*)sig_handler);
while(1)
{
printf("%d\n",i);
sleep(2);
i++;
}


return 0;
}


void sig_handler(int signo)
{

printf("I reveied SIGINT");

}
