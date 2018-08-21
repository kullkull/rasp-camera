#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "queue.h"

//created by Kim jung yeon

extern queue_t irq_queue;


void* detect_service(void* arg){
/*

#	detect_service:
		1. the cam_service transmits data using pipe
		2. read function will be unblocked and data calculations will begin.
		3. if detects intrusion this service will call queue_enqueue function.
*/
    
    
 int wfd , fd, ffd,readn = 1, writen = 0 ;
    char buf[3], buff[3], gar[51];
    float odd = 0.15;
    int i = 0, j = 0, dif = 0;
    float final = 0, result[3];
    queue_element queue_detect={1,0,0};

    while (1)
    {
        i = 0;
        dif = 0;
        readn = 1;
        memset(gar, 0x00, sizeof(gar));

        if (((fd = open("./Temp/image1.bmp", O_RDONLY)) != -1) && ((ffd = open("./Temp/image2.bmp", O_RDONLY)) != -1))
        {
            read(fd, gar, sizeof(gar));
            read(ffd, gar, sizeof(gar));
            while (readn != 0)
            {
                memset(buf, 0x00, 3);
                readn = read(fd, buf, sizeof(buf));
                memset(buff, 0x00, 3);
                readn = read(ffd, buff, sizeof(buff));
                result[0] = (float)(fabs(((float)buff[0] - (float)buf[0]) / 256));
                result[1] = (float)(fabs(((float)buff[1] - (float)buf[1]) / 256));
                result[2] = (float)(fabs(((float)buff[2] - (float)buf[2]) / 256));

                if (result[0] > odd)
                {
                    i++;
                    dif++;
                }
                else if (result[1] > odd)
                {
                    i++;
                    dif++;
                }
                else if (result[2] > odd)
                {
                    i++;
                    dif++;
                }

                else
                {
                    i++;
                }

            }

            final = (float)(dif) / (float)(i);
            if (final < odd)
            {
                //current_status = 0;
            }
            else
            {
		queue_detect.req=IRQ_DET_DETECT;
		queue_enqueue(&irq_queue,queue_detect);
              //current_status = 1;
              
            }
            close(ffd);
            close(fd);
        } //if end

    }       //while end




}
