#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

pthread_t* start_service(void* (*service)(void*),void* arg)
{

pthread_t *id =(pthread_t*)malloc(sizeof(pthread_t));

if(id !=NULL)
{
	pthread_create(id,NULL,service,(void*)arg);
	return id;
}
else
{
	printf("service failed!\n");
	return NULL;
}


}
