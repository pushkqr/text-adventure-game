#include <stdio.h>
#include "mapDimensions.h"

int mapDimensions(void)
{
    char map[10];

    int mapInitialize = 0;
    int mapRoomAssign = 1;


    while(mapInitialize<10)
    {
        map[mapInitialize]='0';

        mapInitialize++;
    }

    while(mapRoomAssign <= 9)
    {
        map[mapRoomAssign] += mapRoomAssign;

        mapRoomAssign++;

    }


    return sizeof(map);

}
