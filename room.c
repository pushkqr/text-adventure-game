#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "room.h"
#include "monster.h"
#include "player.h"

#define NO_EXIT -1
#define ROOM_COUNT 4


//dsd change return to void
//dsd not needed... why here? void roomInIt(Room *room);
//dsd_Bool roomExitVerify(Room *room);

//dsd not all paths return a value warning - changed return to void
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void roomInit(Room *room)
{
	int i = 0;

	for(i = 0; i<DIR_MAX; i++)
		room->list_exit[i] = NO_EXIT;

    strcpy(room->desc,"This cave has horror vibes dude.\n");
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void roomSetExit(Room *room, enum EnumDirection dir, int room_idx)
{
    room->list_exit[dir] = room_idx;
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
bool roomVerifyExits(Room *room, int room_idx)
{
	int i = 0;
	int count;

    count = 0;
    for(i=0; i<DIR_MAX; i++)
    {
        if(room->list_exit[i] == -1)
            count++;
	}

    if(count == 4)
    {
        //dsd try using __FILE__ and __LINE__
        printf("Room [%d] has no exits.\n", room_idx);
        return false;
    }

    return true;
}
