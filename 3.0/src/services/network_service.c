#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "service.h"

#define _LOG_TRUE
#define	_LOG_	"Temp/log-file"
#define MAX_STRING	40
#define _WRITE_LOG(A)	fputs(A,fp)
#define _CLOSE_LOG	fclose(fp)

#ifdef	_LOG_TRUE
extern FILE* fp;
#endif

extern int NET_IRQ;

static	char tmp_str[MAX_STRING];
static	int serv_fd, clnt_fd, serv_port;
static struct sockaddr_in serv_addr, clnt_addr;
static  int len;

static int _wait_for_clnt(void);
static  int _receive_string_from_clnt(void);

void* network_service(void* arg)
{

serv_port = atoi((char*)arg);
#ifdef	_LOG_TRUE
	fp = fopen(_LOG_,"wt");
#endif

#ifdef  _LOG_TRUE
	sprintf(tmp_str, "SERVER: SERVER PORT: %d\n", serv_port);
	_WRITE_LOG(tmp_str);
#endif

	if( (serv_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1   )
	{
#ifdef  _LOG_TRUE
		_WRITE_LOG("Socket ERR\n");
		_CLOSE_LOG;
#endif
		return NULL;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	memset(&clnt_addr, 0, sizeof(clnt_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(serv_port);

 	if (bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    	{
#ifdef  _LOG_TRUE
  		_WRITE_LOG("Bind ERR\n");
		_CLOSE_LOG;
#endif
		return NULL;
    	}

	if (listen(serv_fd, 5)<0)
	{
#ifdef  _LOG_TRUE
		_WRITE_LOG("Listen ERR\n");
		_CLOSE_LOG;
#endif
		return NULL;
    	}

	len = sizeof(clnt_addr);

	while(_wait_for_clnt())
	{
		NET_IRQ=_receive_string_from_clnt();
	}
		_CLOSE_LOG;
}

static int _wait_for_clnt(void)
{

	if(     (clnt_fd = accept(serv_fd, (struct sockaddr*)&clnt_addr, &len))   == -1        )
	{
#ifdef  _LOG_TRUE
		_WRITE_LOG("Accept ERR\n");
		_CLOSE_LOG;
#endif
		return 0;
	}
#ifdef	_LOG_TRUE
	char clnt_ip_addr[20];
	inet_ntop(AF_INET, &clnt_addr.sin_addr.s_addr, clnt_ip_addr, sizeof(clnt_ip_addr));
        sprintf(tmp_str, "SERVER: %s client connected \n", clnt_ip_addr);
	_WRITE_LOG(tmp_str);
#endif
		return 1;
}

static  int _receive_string_from_clnt(void)
{
	char  recevbuff[MAX_STRING];
	read(clnt_fd,recevbuff,MAX_STRING-1);

	if 	(	!strcmp(recevbuff, "status"	)	)
		return 	0;
        else if (	!strcmp(recevbuff,"imagereq")	)
		return 	1;
	else
		return -1;
}
void _send_data_to_clnt(int option)
{
switch(option){
	case  0 :
#ifdef  _LOG_TRUE
                _WRITE_LOG("string \"status\" received \n");
                _CLOSE_LOG;
#endif
		break;
	case  1 :
#ifdef  _LOG_TRUE
                _WRITE_LOG("string \"imagereq\" reveived \n");
                _CLOSE_LOG;
#endif
		break;

	case -1 :
#ifdef  _LOG_TRUE
                _WRITE_LOG("Error occured while reading string from clnt \n");
                _CLOSE_LOG;
#endif

		break;

    default:
		break;

}

}
