
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


void initRooms(void);
void initMonster(void);
void dirMove(void);
void arrayOrganize(void);
void actionLook(void);
void actionInventory(void);
void delay(int sec);
int monsterAttackMenu(void);


#define NUM_ROOM 4


#define ITEM_COUNT_MAX 3
int room_curr_idx;
Command command_curr;
Room room_list[NUM_ROOM];
Player p1 = {30,5};



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
int main()
{
    bool is_game_over;


    int monster_attack_idx = 0;


    printf("\n");
    printf("Welcome to CaveExplorer\n");
    printf("Use \"help\" for hints.\n");

    is_game_over = false;

    initRooms();
    initMonster();

    while (!is_game_over)
    {
        printf("\n< You are currently in room [%d]. >\n", room_curr_idx + 1);

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
                printf("\n\"(N)orth\" : moves in the north direction\n");
                printf("\n\"(S)outh\" : moves in the south direction\n");
                printf("\n\"(E)ast\" : moves in the east direction\n");
                printf("\n\"(W)est\" : moves in the west direction\n");
                printf("\n\"look\" : looks around\n");
                printf("\n\"pickup\" : opens up the item pickup menu\n");
                printf("\n\"drop\" : opens up the item drop menu\n");
                printf("\n\"attack\" : attacks nearby monsters\n");
                printf("\n\"quit\" : procedes to quit the game\n");
                break;
            case QUIT:
                printf("\nBye!\n");
                is_game_over = true;
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
                        is_game_over = true;
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
			case INVENTORY:
				actionInventory();
				break;
            case INVALID:
                printf("\n< Cannot understand the command [%s]. >\n", command_curr.buffer);
                break;
        }
    }

    return 0;
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void initRooms()
{
    int i;

    for(i = 0; i < NUM_ROOM; i++ )
        roomInit(&room_list[i]);

    roomSetExit(&room_list[0], DIR_SOUTH, 1);

    roomSetExit(&room_list[1], DIR_NORTH, 0);
    roomSetExit(&room_list[1], DIR_EAST,  2);
    roomSetExit(&room_list[1], DIR_WEST,  3);

    roomSetExit(&room_list[2], DIR_WEST,  1);

    roomSetExit(&room_list[3], DIR_EAST,  1);


    for(i=0; i<NUM_ROOM; i++)
    {
        if(!roomVerifyExits(&room_list[i], i))
            exit(0);
    }

    ////room1
    strcpy(room_list[0].item_list[0].name ,"ROCK");
    strcpy(room_list[0].item_list[1].name ,"AWP");
    strcpy(room_list[0].item_list[2].name ,"STICK");

    ////room2
    strcpy(room_list[1].item_list[0].name ,"POLE");
    strcpy(room_list[1].item_list[1].name ,"ROD");
    strcpy(room_list[1].item_list[2].name ,"CHAIN");

    ////room3
    strcpy(room_list[2].item_list[0].name ,"CAPE");
    strcpy(room_list[2].item_list[1].name ,"SACK");
    strcpy(room_list[2].item_list[2].name ,"KNIFE");

}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void initMonster()
{
    int i;

    for (i=0; i<NUM_ROOM; i++)
    {
        for (int j = 0; j < MONSTER_COUNT_MAX;j++)
        {
            strcpy(room_list[i].monster_list[j].monsterName, "");
            strcpy(p1.inventory[i].name,"");
        }
    }

    monsterInit(&room_list[3].monster_list[0]);

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
    else if(strcmp(command_curr.buffer,"INVENTORY")==0)
        command_curr.cmd = INVENTORY;
    else
        command_curr.cmd = INVALID;
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void dirMove(void)
{
        if(command_curr.cmd >= DIR_NORTH && command_curr.cmd <= DIR_WEST)
    {
        if(room_list[room_curr_idx].list_exit[command_curr.cmd] != (-1))
        {
            room_curr_idx = room_list[room_curr_idx].list_exit[command_curr.cmd];
        }
        else
        {
            printf("\n< Can't go to %s right now... >\n", command_curr.buffer);
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
        if(strcmp(room_list[room_curr_idx].monster_list[i].monsterName,"") != 0)
        {
            printf("\n%d. [%s]\n", i + 1, room_list[room_curr_idx].monster_list[i].monsterName);
        }

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


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void actionLook()
{
    int i = 0;
    int j = 0;

    printf("\n%s", room_list[room_curr_idx].desc);

    for(j = 0; j<MONSTER_COUNT_MAX;j++)
    {
        if(strcmp(room_list[room_curr_idx].monster_list[j].monsterName, "") != 0)
        {
            printf("\nbruh monster! fight or flight.\n");
        }
    }

    for(i=0; i<NUM_ROOM; i++)
    {
        if(room_list[room_curr_idx].list_exit[i] != -1)
        {
            int temp = room_list[room_curr_idx].list_exit[i];
            for(j = 0; j<MONSTER_COUNT_MAX;j++)
            {
                if(strcmp(room_list[temp].monster_list[j].monsterName, "") != 0)
                {
                    printf("\nbruh monster nearby.\n");
                }
            }
        }
    }

    printf("\nItems ~");

    for( i = 0; i < ITEM_COUNT_MAX; i++)
    {
        if(strcmp(room_list[room_curr_idx].item_list[i].name,"")!= 0)
			printf("\n[%s]\n", room_list[room_curr_idx].item_list[i].name);
    }

	printf("\nExits ~\n");

    for( i = 0; i < DIR_MAX; i++)
    {
		if(room_list[room_curr_idx].list_exit[i] != -1)
		{
			switch(i)
			{
				case 0:
					printf("(N)orth ~ [room %d]", room_list[room_curr_idx].list_exit[i]+1);
					break;
				case 1:
					printf("(S)outh ~ [room %d]", room_list[room_curr_idx].list_exit[i]+1);
					break;
				case 2:
					printf("(E)ast ~ [room %d]", room_list[room_curr_idx].list_exit[i]+1);
					break;
				case 3:
					printf("(W)est ~ [room %d]", room_list[room_curr_idx].list_exit[i]+1);
					break;
			}
			printf("\n");
		}

    }


}

void actionInventory(void)
{
	int i = 0;
	int count =0;

	for(i - 0; i < PLAYER_ITEM_MAX; i++)
	{
        if(strcmp(p1.inventory[i].name,"") == 0)
        {
            count++;
        }
	}

	printf("\nPlayer Inventory [%d / %d]\n", PLAYER_ITEM_MAX - count, PLAYER_ITEM_MAX );
	for(i = 0; i < PLAYER_ITEM_MAX;i++)
	{
		if(strcmp(p1.inventory[i].name,"") != 0)
		{
			printf("\n[%s]\n", p1.inventory[i].name);

		}
	}
}
