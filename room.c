#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "room.h"
#include "monster.h"
#include "player.h"

#define NO_EXIT -1
#define ROOM_COUNT 4


int roomInIt(Room *room);
_Bool roomExitVerify(Room *room);

int roomInIt(Room *room)
{
	int i = 0;

	for(i = 0; i<4; i++)
	{
		room->exits[i] = NO_EXIT;
	}

    strcpy(room->desc,"This cave has horror vibes dude.\n");
}

_Bool roomExitVerify(Room *room)
{
	int i = 0;
	int count =0;

    for(i=0;i<4;i++)
    {

        if(room->exits[i] == -1)
        {
            count++;
        }

        if(count == 4)
		{
            printf("Error loading the map.\n");
            return false;
		}

	}

	return true;
}
