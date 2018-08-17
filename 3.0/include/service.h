#ifndef _SERVICE_H_
#define _SERVICE_H_
#include <pthread.h>
pthread_t* start_service(void* (*service)(void*),char *arg);
void*	camera_service(void*);
void*   detect_service(void*);

void _send_data_to_clnt(int option);

#endif

