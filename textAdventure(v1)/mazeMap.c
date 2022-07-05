#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mazeMap(void)
{
    char mazeSize[10];
    int mazeInitialize = 0;
    int mazeRoomLabel = 1;


    while(mazeInitialize<10)
    {
        mazeSize[mazeInitialize]='0';

        mazeInitialize++;
    }

    while(mazeRoomLabel <= 9)
    {
        mazeSize[mazeRoomLabel] += mazeRoomLabel;

        mazeRoomLabel++;

    }


    return sizeof(mazeSize) / 2;

}
