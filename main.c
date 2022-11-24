#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>



#include "userTypes.h"
#include "room.h"
#include "monster.h"
#include "player.h"
#include "item.h"
#include "command.h"

#define NO_EXIT -1
#define N 0
#define S 1
#define E 2
#define W 3
#define ROOM_COUNT 4
#define ITEM_COUNT_MAX 3


_Bool initRooms();
_Bool initMonster();
void dirMove(void);
void arrayOrganize(void);
void actionLook(void);
void delay(int sec);
int monsterAttackMenu(void);
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

int room_curr_idx;

Command command_curr;

Room room_list[ROOM_COUNT];

Player p1 = {30,5};
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
int main()
{
    int loop_break = 0;
    int monster_attack_idx = 0;
    int item_idx;

    printf("\n      Welcome to CaveExplorer        \n");

    printf("\nHINT:Try using the \"help\" action.\n");

    initMonster();

    while (loop_break != (-1))
    {
        printf("\nYou are currently in room [%d].\n", room_curr_idx + 1);

		initRooms();
        getCommand();
        arrayOrganize();

        switch (command_curr.cmd)
        {
            case NORTH:
            case SOUTH:
            case EAST:
            case WEST:
                dirMove();
                break;
            case HELP:
                printf("\nSearch the rooms for your desired treasure but beware of the UNKNOWN!....\n");
                printf("\n\"north\" : moves in the north direction");
                printf("\n\"south\" : moves in the south direction");
                printf("\n\"east\" : moves in the east direction");
                printf("\n\"west\" : moves in the west direction");
                printf("\n\"quit\" : procedes to quit the game\n");
                break;
            case QUIT:
                printf("\nBye!\n");
                loop_break = -1;
                break;
            case ATTACK:
                monster_attack_idx = monsterAttackMenu();
                if(monster_attack_idx == -1)
                    break;
                else
                {
                    playerAttack(&room_list[room_curr_idx].monster_list[monster_attack_idx], &p1);
                    if(monsterAttack(&room_list[room_curr_idx].monster_list[monster_attack_idx], &p1) == true)
                    {
                        delay(2);
                        loop_break = -1;
                    }
                    break;
                }
            case PICKUP:
                item_pickup(&p1, &room_list[room_curr_idx]);
                break;
            case DROP:
                item_drop(&p1, &room_list[room_curr_idx]);
                break;
            case LOOK:
                actionLook();
                break;
            case INVALID:
                printf("\nCannot understand the command [%s].\n", command_curr.buffer);
                break;
        }
    }

    return 0;
}
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void getCommand()
{
    char *p = command_curr.buffer;

    strcpy(command_curr.buffer,"");

    printf("\n[-->");
    scanf("%19s", command_curr.buffer);

    for(int i = 0; i<strlen(command_curr.buffer); i++)
    {
        *(p+i) = toupper( *(p+i) );
    }

    assignEnumCmd();

}
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void assignEnumCmd(void)
{
    if(strcmp(command_curr.buffer,"NORTH")==0 || strcmp(command_curr.buffer,"N")==0)
        command_curr.cmd = NORTH;
    else if(strcmp(command_curr.buffer,"SOUTH")==0 || strcmp(command_curr.buffer,"S")==0)
        command_curr.cmd = SOUTH;
    else if(strcmp(command_curr.buffer,"EAST")==0 || strcmp(command_curr.buffer,"E")==0)
        command_curr.cmd = EAST;
    else if(strcmp(command_curr.buffer,"WEST")==0 || strcmp(command_curr.buffer,"W")==0)
        command_curr.cmd = WEST;
    else if(strcmp(command_curr.buffer,"QUIT")==0)
        command_curr.cmd = QUIT;
    else if(strcmp(command_curr.buffer,"HELP")==0)
        command_curr.cmd = HELP;
    else if(strcmp(command_curr.buffer,"ATTACK")==0)
        command_curr.cmd = ATTACK;
    else if(strcmp(command_curr.buffer,"PICKUP")==0)
        command_curr.cmd = PICKUP;
    else if(strcmp(command_curr.buffer,"DROP")==0)
        command_curr.cmd = DROP;
    else if(strcmp(command_curr.buffer,"LOOK")==0)
        command_curr.cmd = LOOK;
    else
        command_curr.cmd = INVALID;
}
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
_Bool initRooms()
{

	for(int i = 0; i < ROOM_COUNT;i++ )
	{
        roomInIt(&room_list[i]);
    }

    room_list[0].exits[S] =  1;

    room_list[1].exits[N] =  0;
    room_list[1].exits[E] =  2;
    room_list[1].exits[W] =  3;

    room_list[2].exits[W] =  1;

    room_list[3].exits[E] =  1;

	for(int i = 0; i < ROOM_COUNT;i++ )
	{
			if(roomExitVerify(&room_list[i]) == false)
            {
                exit(0);
            }
	}

    ////room1
    strcpy(room_list[0].item_list[0].name ,"Rock");
    strcpy(room_list[0].item_list[1].name ,"Cloth Rags");
    strcpy(room_list[0].item_list[2].name ,"Stick");

    ////room2
    strcpy(room_list[1].item_list[0].name ,"Rusted Sword");
    strcpy(room_list[1].item_list[1].name ,"Metal Pole");
    strcpy(room_list[1].item_list[2].name ,"Chain");

    ////room3
    strcpy(room_list[2].item_list[0].name ,"Cape");
    strcpy(room_list[2].item_list[1].name ,"Sack");
    strcpy(room_list[2].item_list[2].name ,"Damaged Halberd");

}

_Bool initMonster()
{
    for (int i = 0; i < ROOM_COUNT;i++)
    {
        for (int j = 0; j < MONSTER_COUNT_MAX;j++)
        {
            strcpy(room_list[i].monster_list[j].monsterName, "");
            strcpy(p1.inventory[i].name,"");
        }
    }

    monsterInit(&room_list[3].monster_list[0]);

}

void dirMove(void)
{
    if(command_curr.cmd >= N && command_curr.cmd <= W)
    {
        if(room_list[room_curr_idx].exits[command_curr.cmd] != (-1))
        {
            room_curr_idx = room_list[room_curr_idx].exits[command_curr.cmd];
        }
        else
        {
            printf("\nCan't go to %s right now...\n", command_curr.buffer);
        }
    }

}
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
int monsterAttackMenu(void)
{
    int i = 0;
    int result = 0;

    for (i = 0; i < (sizeof(room_list[room_curr_idx].monster_list)/sizeof(Monster)); i++ )
    {

        printf("\n%d. [%s]\n", i + 1, room_list[room_curr_idx].monster_list[i].monsterName);
    }

        printf("\n[-->");
        scanf("%d", &result);

    if(result > i || result < 0 || strcmp(room_list[room_curr_idx].monster_list[result-1].monsterName, "") == 0)
    {
        printf("\nInvalid Choice.\n");
        return (-1);
    }
    else
    {
        return ( result-1 );
    }

}
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void arrayOrganize()
{
    int i = 0;
    int j = 0;

    ////organise room items
    for(i= 0; i<4; i++)
    {
        for(j=0 ;j<2; j++)
        {
            if(strcmp(room_list[i].item_list[j].name,"")==0 && strcmp(room_list[i].item_list[j+1].name,"") != 0 )
            {
                strcpy(room_list[i].item_list[j].name, room_list[i].item_list[j+1].name);

                strcpy(room_list[i].item_list[j+1].name,"");
            }

        }
    }
    ////organise player inventory
    for(j=0 ;j<4; j++)
    {
        if(strcmp(p1.inventory[j].name,"")==0 && strcmp(p1.inventory[j+1].name,"") == 1 )
        {
            strcpy(p1.inventory[j].name, p1.inventory[j+1].name);

            strcpy(p1.inventory[j+1].name,"");
        }

    }

}
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void delay(int sec)
{
    int milliSec = 1000 * sec;

    clock_t startTime = clock();

    while (clock() < startTime + milliSec)
        ;
}

void actionLook()
{
    int i = 0;
    int j = 0;

    printf("%s", room_list[room_curr_idx].desc);

    for(j = 0; j<MONSTER_COUNT_MAX;j++)
    {
        if(strcmp(room_list[room_curr_idx].monster_list[j].monsterName, "") != 0)
        {
            printf("\nbruh monster! fight or flight.\n");
        }
    }

    for(i = 0; i<ROOM_COUNT; i++)
    {
        if(room_list[room_curr_idx].exits[i] != -1)
        {
            int viableExit = room_list[room_curr_idx].exits[i];
            for(j = 0; j<MONSTER_COUNT_MAX;j++)
            {
                if(strcmp(room_list[viableExit].monster_list[j].monsterName, "") != 0)
                {
                    printf("\nbruh monster nearby.\n");
                }
            }
        }
    }

    printf("\nItems ~");

    for( i = 0; i < ITEM_COUNT_MAX; i++)
    {
        printf("\n[%s]\n", room_list[room_curr_idx].item_list[i].name);
    }

}
