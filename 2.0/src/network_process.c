#include "define.h"
#include "types/shared_data.h"
#include "locate_shared_data.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ipc.h>

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/select.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <sys/msg.h>

extern char status_ok[10];
extern char status_not_ok[14];
extern int Detected;
extern int Donotpic;

pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;

void*network_process(void* argv)
{
    key_t SHARED_KEY;
    int data_fd;
    int data_pt = 0;
    char data_temp[MAX_ARR_SIZE];
    char data[MAX_ARR_SIZE];
    char received_data[MAX_ARR_SIZE];
    SHARED_DATA shared_data;
    memset(data, 0, sizeof(data));
    memset(&shared_data, 0, sizeof(shared_data));

    //shared msgget()------------------------------------------------------------
    SHARED_KEY = msgget((key_t)SHARED_KEY_VAL, IPC_CREAT | 0666);
    if (SHARED_KEY == -1)
    {
        printf("failed to create SHARED_KEY\n");
        exit(1);
    }
    //printf("RASPBERRY SERVER STARTED\n\n ");

    pthread_mutex_lock(&mutex);

    shared_data.SHARED_DATA_TYPE = 1;
    strcpy(locate_shared_data(&shared_data, ((data_pt++) % SHARED_DATA_NUM) + 1), "SERVER: RASPBERRY SERVER STARTED\n\n");
    msgsnd(SHARED_KEY, &shared_data, sizeof(shared_data) - sizeof(long), 0);
    pthread_mutex_unlock(&mutex);

    //----------------------------------------------------------------------------------------------------------------
    int serv_fd;
    int clnt_fd;
    int serv_port = atoi((char*)argv);

    pthread_mutex_lock(&mutex);
    //printf("SERVER: 서버 포트: %d\n",serv_port);
    sprintf(data_temp, "SERVER: SERVER PORT: %d\n", serv_port);
    strcpy(locate_shared_data(&shared_data, ((data_pt++) % SHARED_DATA_NUM) + 1), data_temp);
    msgsnd(SHARED_KEY, &shared_data, sizeof(shared_data) - sizeof(long), 0);
    pthread_mutex_unlock(&mutex);

    serv_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (serv_fd == -1)
    {
        printf("SOCKET ERROR");
        exit(1);
    }

    struct sockaddr_in serv_addr, clnt_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&clnt_addr, 0, sizeof(clnt_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(serv_port);


    pthread_mutex_lock(&mutex);
    //printf("RASPBERRY IS CURRENTLY BINDING ...\n");
    strcpy(locate_shared_data(&shared_data, ((data_pt++) % SHARED_DATA_NUM) + 1), "RASPBERRY IS CURRENTLY BINDING ...\n");
    msgsnd(SHARED_KEY, &shared_data, sizeof(shared_data) - sizeof(long), 0);
    pthread_mutex_unlock(&mutex);


    if (bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("RASPBERRY BIND() FAILED!!!!!!!!!!!!!!!!!!!!! ...\n");
        exit(1);
    }

    if (listen(serv_fd, 5)<0)
    {
        printf("RASPBERRY LISTEN() FAILED!!!!!!!!!!!!!!!!!!!\n");
        exit(1);
    }


    pthread_mutex_lock(&mutex);
    //printf("RASPBERRY IS CURRENTLY LISTENING.\n");
    strcpy(locate_shared_data(&shared_data, ((data_pt++) % SHARED_DATA_NUM) + 1), "RASPBERRY IS CURRENTLY LISTENING.\n");
    msgsnd(SHARED_KEY, &shared_data, sizeof(shared_data) - sizeof(long), 0);
    pthread_mutex_unlock(&mutex);

    //char  sendbuff[MAX_ARR_SIZE]="SERVER: CONNECTION SUCESSFUL!!!\n";
    char  recevbuff[MAX_ARR_SIZE];

    int len = sizeof(clnt_addr);

    while (1)
    {
        data_fd = open("image2.bmp", O_RDONLY);

        if (data_fd == -1)
        {
            //printf("Please ADD serv_in file in our directory\n");
            //exit(1);
            system("touch serv_in");
        }
        clnt_fd = accept(serv_fd, (struct sockaddr*)&clnt_addr, &len);
        int readn = 0;
        if (clnt_fd <0)
        {
            printf("RASPBERRY ACCEPT() FAILED \n");
            //exit(1);
        }

        char clnt_ip_addr[100];

        inet_ntop(AF_INET, &clnt_addr.sin_addr.s_addr, clnt_ip_addr, sizeof(clnt_ip_addr));
        pthread_mutex_lock(&mutex);
        if ((data_pt % SHARED_DATA_NUM) == 0)
        {
            long temp = shared_data.SHARED_DATA_TYPE;
            memset(&shared_data, 0, sizeof(shared_data));
            shared_data.SHARED_DATA_TYPE = temp;
        }
        sprintf(data_temp, "SERVER: %s client connected \n", clnt_ip_addr);
        //printf("SERVER: %s client connected \n",clnt_ip_addr);
        strcpy(locate_shared_data(&shared_data, ((data_pt++) % SHARED_DATA_NUM) + 1), data_temp);
        msgsnd(SHARED_KEY, &shared_data, sizeof(shared_data) - sizeof(long), 0);
        pthread_mutex_unlock(&mutex);


        /*
        {
        }
        */
        memset(data, 0, sizeof(data));
        memset(received_data, 0, sizeof(received_data));
        read(clnt_fd, received_data, MAX_ARR_SIZE - 1);
        if (!strcmp(received_data, "status"))
        {
            if (Detected == 0)
            {
                write(clnt_fd, status_ok, strlen(status_ok));
            }
            else
            {
                write(clnt_fd, status_not_ok, strlen(status_not_ok));
            }

        }
        else if (!strcmp(received_data, "imagereq"))
        {
            while (readn = read(data_fd, data, MAX_ARR_SIZE - 1))
            {
                write(clnt_fd, data, readn);
                memset(data, 0, sizeof(data));

            }
            Donotpic = 0;
        }



        close(clnt_fd);

        pthread_mutex_lock(&mutex);
        if ((data_pt % SHARED_DATA_NUM) == 0)
        {
            long temp = shared_data.SHARED_DATA_TYPE;
            memset(&shared_data, 0, sizeof(shared_data));
            shared_data.SHARED_DATA_TYPE = temp;
        }



        //printf("SERVER: Connection Sucessfully Closed\n");
        strcpy(locate_shared_data(&shared_data, ((data_pt++) % SHARED_DATA_NUM) + 1), "SERVER: Connection Sucessfully Closed\n");
        msgsnd(SHARED_KEY, &shared_data, sizeof(shared_data) - sizeof(long), 0);
        pthread_mutex_unlock(&mutex);

    }

}




