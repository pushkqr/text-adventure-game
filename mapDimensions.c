#include <stdio.h>
#include "mapDimensions.h"

int mapDimensions(void)
{
    char map[18];

    int mapInitialize = 0;
    int mapRoomAssign = 1;


    while(mapInitialize<18)
    {
        map[mapInitialize]='0';

        mapInitialize++;
    }

    while(mapRoomAssign <= 18)
    {
        map[mapRoomAssign] += mapRoomAssign;

        mapRoomAssign++;

    }


    return sizeof(map);

}
