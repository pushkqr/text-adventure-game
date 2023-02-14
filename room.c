#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"
#include "room.h"
#include "monster.h"
#include "player.h"

#define NO_EXIT -1
#define ROOM_COUNT 4


//dsd change return to void
//dsd not needed... why here? void roomInIt(Room *room);
//dsd_Bool roomExitVerify(Room *room);

//dsd not all paths return a value warning - changed return to void

bool isMonsterInRoom(Room *room);
void displayMonsters(Room *room);
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
        //pio couldnt find how to properly use these
        //dsd try using __FILE__ and __LINE__
        printf("Room [%d] has no exits.\n", room_idx);
        return false;
    }

    return true;
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void roomDisplay(int room_idx, Room *room)
{
    //dsd should also auto show whats in the room
    int i = 0;

    printf("\n< You are currently in room [%d]. >\n", room_idx + 1);

	printf("\nExits ~\n");

    for(i = 0; i < DIR_MAX; i++)
    {
		if(room->list_exit[i] != -1)
		{
			switch(i)
			{
				case 0:
					printf("(N)orth ~ [room %d]", room->list_exit[i]+1);
					break;
				case 1:
					printf("(S)outh ~ [room %d]", room->list_exit[i]+1);
					break;
				case 2:
					printf("(E)ast ~ [room %d]", room->list_exit[i]+1);
					break;
				case 3:
					printf("(W)est ~ [room %d]", room->list_exit[i]+1);
					break;
			}
			printf("\n");
		}

    }

    if(isMonsterInRoom(room) == true)
    {
        printf("Bruh monster! Fight or FLIGHT!!!.\n");

        displayMonsters(room);

    }

}
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
bool roomAddItem(Room *room, char *item, int dmg)
{
    int i = 0;

    for(i = 0; i < ROOM_ITEM_MAX; i++)
    {
        if(strcmp(room->item_list[i].name,"") == 0)
        {
            strcpy(room->item_list[i].name, item);
            room->item_list[i].dps = dmg;
            return true;
        }
    }

    return false;
}

bool isMonsterInRoom(Room *room)
{
    int j=0;

    for(j = 0; j<MONSTER_COUNT_MAX;j++)
    {
        if(strcmp(room->monster_list[j].monsterName, "") != 0)
        {
            return true;
        }
    }

    return false;
}

void displayMonsters(Room *room)
{
    int i = 0;

    for(i = 0; i<MONSTER_COUNT_MAX; i++)
    {
        if(strcmp(room->monster_list[i].monsterName, "") != 0)
        {
            printf("\n[%s]  ~   [%d hps]\n", room->monster_list[i].monsterName, room->monster_list[i].hps);
        }
    }
}




