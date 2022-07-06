#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mazeMap(void)
{
    char maze[10];

    int mazeInitialize = 0;
    int mazeRoomLabel = 1;


    while(mazeInitialize<10)
    {
        maze[mazeInitialize]='0';

        mazeInitialize++;
    }

    while(mazeRoomLabel <= 9)
    {
        maze[mazeRoomLabel] += mazeRoomLabel;

        mazeRoomLabel++;

    }


    return sizeof(maze);

}
