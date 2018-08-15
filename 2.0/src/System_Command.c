#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "define.h"
int System_Command(char* Command_in, char Data_out[])
{
    FILE *fp;
    char path[MAX_ARR_SIZE];
    memset(path, 0, sizeof(path));
    int c = -1;
    int i = 0;


    /* Open the command for reading. */
    fp = popen(Command_in, "r");
    if (fp == NULL)
    {
        return -1;
    }

    while (c != 0)
    {
        c = fgetc(fp);
        if (c == EOF || i >= (MAX_ARR_SIZE - 1))
        {
            c = 0;
        }
        path[i++] = c;
    }


    strcpy(Data_out, path);
    /* close */
    pclose(fp);
    return 0;

}


