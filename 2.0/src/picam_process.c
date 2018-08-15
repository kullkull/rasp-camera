#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include "define.h"

extern int Detected;
extern int saveimagesuffix;
extern int Donotpic;
extern char saveimage[MAX_ARR_SIZE_S];

void* picam_process(void*argv)
{


    int wfd;
    int fd;
    int ffd;
    int readn = 1;
    int writen = 0;
    char buf[3];
    char buff[3];
    char gar[51];
    float odd = 0.15;
    int i = 0;
    int j = 0;
    int dif = 0;
    float final = 0;
    float result[3];
    while (1)
    {
        i = 0;
        dif = 0;
        readn = 1;
        memset(gar, 0x00, sizeof(gar));


        system("raspistill -o image1.bmp -e bmp -h 102 -w 102 -n -t 1 >/dev/null 2>&1");
        system("raspistill -o image2.bmp -e bmp -h 102 -w 102 -n -t 1 >/dev/null 2>&1");

        if (((fd = open("image1.bmp", O_RDONLY)) != -1) && ((ffd = open("image2.bmp", O_RDONLY)) != -1))
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
                Detected = 0;
            }
            else
            {
                saveimagesuffix++;
                memset(saveimage, 0, sizeof(saveimage));
                sprintf(saveimage, "cp image2.bmp detection_%d", saveimagesuffix);
                system(saveimage);
                Detected = 1;
                system("php php/push_notification.php");
                Donotpic = 1;
            }
            close(ffd);
            close(fd);
        } //if end

    }       //while end

} // thread _end



