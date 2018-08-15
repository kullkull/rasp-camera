#include "define.h"
#include "types/shared_data.h"


char* locate_shared_data(SHARED_DATA *shared_data, int i)
{
    if (i == 1)
    {
        return (char*)((*shared_data).DATA1);
    }
    else if (i == 2)
    {
        return (char*)((*shared_data).DATA2);
    }
    else if (i == 3)
    {
        return (char*)((*shared_data).DATA3);
    }
    else if (i == 4)
    {
        return (char*)((*shared_data).DATA4);
    }
    else if (i == 5)
    {
        return (char*)((*shared_data).DATA5);
    }
    else if (i == 6)
    {
        return (char*)((*shared_data).DATA6);
    }
    else if (i == 7)
    {
        return (char*)((*shared_data).DATA7);
    }
    else if (i == 8)
    {
        return (char*)((*shared_data).DATA8);
    }
    else if (i == 9)
    {
        return (char*)((*shared_data).DATA9);
    }

}

