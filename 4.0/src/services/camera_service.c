#include <stdlib.h>



void* camera_service(void* arg)
{
//int* fd = (int*)arg;

   system("raspistill -o ./Temp/image1.bmp -e bmp -h 102 -w 102 -n -t 1 >/dev/null 2>&1");
    system("raspistill -o ./Temp/image2.bmp -e bmp -h 102 -w 102 -n -t 1 >/dev/null 2>&1");
     
}
