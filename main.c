//dsd if i have just 'dsd' alone it's just a note to myself that i
//      still need to look at that thing
//      you should start having your own initial in the code as well
//      i.e. p?o (pio?)
//         int x_alt;   //pio - don't like this var name - change tit to something better
//         you use it to not forgot that something isnt clean
// pio still need to sort the code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "room.h"
#include "monster.h"
#include "player.h"
#include "item.h"
#include "command.h"


void initRooms(void);
void initMonster(void);
void arrayOrganize(void);
void handleCommandMove(void);
bool handleCommandAttack(void);
void handleCommandLook(void);
void handleCommandInventory(void);
bool isEqual(char *str1, char *str2);
void handleDirection(Command *c);

//dsd
void delay(int sec);
int monsterAttackMenu(void);


//dsd reorganized vars to be together with related types
Command command_curr;

#define NUM_ROOM 4
Room room_list[NUM_ROOM];
int room_curr_idx;

//dsd
#define ITEM_COUNT_MAX 3

//dsd
Player p1 = {30,5};
//char *verb;
//char *noun;



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
int main()
{

    bool is_game_over;

    printf("\n");
    printf("Welcome to CaveExplorer\n");
    printf("Use \"help\" for hints.\n");

    is_game_over = false;

    initRooms();
    initMonster();

    while (!is_game_over)
    {

        roomDisplay(room_curr_idx);

		getCommand();


        if( isEqual(command_curr.verb, "QUIT") == true)
        {
                printf("\nBye!\n");
                is_game_over = true;
        }
        else if(isEqual(command_curr.verb, "MOVE") == true )
        {
            handleCommandMove();
        }
        else if(isEqual(command_curr.verb, "HELP") == true)
        {
            handleCommandHelp();
        }
        else if(isEqual(command_curr.verb, "LOOK") == true)
        {
            handleCommandLook();
        }
        else if( isEqual(command_curr.verb,"PICKUP") == true)
        {
            handleItemPickup(&p1, &room_list[room_curr_idx], &command_curr);
        }
        else if(isEqual(command_curr.verb, "INVENTORY") == true)
        {
            handleCommandInventory();
        }
        else if (isEqual(command_curr.verb, "DROP") == true)
        {
            handleItemDrop(&p1, &room_list[room_curr_idx], &command_curr);
        }
        else
        {
            printf("\nInvalid Command.\n");
            printf("Try using \"help\".\n");
        }
       /* switch (command_curr.cmd)
        {

            case ATTACK:
                if (handleCommandAttack())
                    is_game_over = true;
                break;

            //dsd
            case PICKUP:
                item_pickup(&p1, &room_list[room_curr_idx]);
                break;

            //dsd
            case DROP:
                item_drop(&p1, &room_list[room_curr_idx]);
                break;

            case LOOK:
                handleCommandLook();
                break;

            case INVENTORY:
                handleCommandInventory();
				break;

            case INVALID:
                printf("\n< Cannot understand the command [%s]. >\n", command_curr.buffer);
                break;
        }*/
    }

    return 0;
}



//dsd
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
    roomAddItem(&room_list[0], "ROCK");
    roomAddItem(&room_list[0], "AWP");
    roomAddItem(&room_list[0], "STICK");

    ////room2
    roomAddItem(&room_list[1], "POLE");
    roomAddItem(&room_list[1], "ROD");
    roomAddItem(&room_list[1], "CHAIN");

    ////room3
    roomAddItem(&room_list[2], "CAPE");
    roomAddItem(&room_list[2], "SACK");
    roomAddItem(&room_list[2], "KNIFE");

}

//dsd
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

//dsd
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void getCommand()
{
    char *p = command_curr.buffer;

    strcpy(command_curr.buffer,"");
    strcpy(command_curr.verb,"");
    strcpy(command_curr.noun,"");

    printf("\n[-->");
    fgets(command_curr.buffer, sizeof(command_curr.buffer)/sizeof(char), stdin);

    for(int i = 0; i<strlen(command_curr.buffer); i++)
    {
        *(p+i) = toupper( *(p+i) );
    }

    sscanf(command_curr.buffer, "%s %s", command_curr.verb,command_curr.noun);

  //  printf("verb-%s noun-%s\n", command_curr.verb, command_curr.noun);
 //   assignEnumCmd(&command_curr);

}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void handleCommandMove(void)
{
    handleDirection(&command_curr);

    if(command_curr.cmd >= DIR_NORTH && command_curr.cmd <= DIR_WEST)
    {
        if(room_list[room_curr_idx].list_exit[command_curr.cmd] != (-1))
            room_curr_idx = room_list[room_curr_idx].list_exit[command_curr.cmd];
        else
            printf("\n< Can't go to %s right now... >\n", command_curr.noun);
    }
    //dsd what if something else came into this function - should give an full
    //dsd error command with desc + __FILE__ + __LINE__

}


//pio still need to work on attack
//dsd i could've made is_game_over global - but i'd rather not
//      so instead i return true/false if the player has died
//////////////////////////////////////////////////////////////////////////
//
// returns true if player has died
//
//////////////////////////////////////////////////////////////////////////
/*bool handleCommandAttack(void)
{
    //dsd dump this whole menu thing
    //  just save 'attack monster'
    //  later it can work as 'attack dwarf' etc
    int monster_attack_idx = 0;

    monster_attack_idx = monsterAttackMenu();
    if(monster_attack_idx == -1)
    {
        return false;
    }
    else
    {
        playerAttack(&room_list[room_curr_idx].monster_list[monster_attack_idx], &p1);
        if(monsterAttack(&room_list[room_curr_idx].monster_list[monster_attack_idx], &p1) == true)
        {
            //dsd why do we need the delay stuff?
            delay(2);
            return true;
        }
    }

    return false;
}*/

//dsd
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

//dsd
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
/*void arrayOrganize()
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

}*/

//dsd
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


//dsd
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void handleCommandLook()
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

//dsd
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void handleCommandInventory(void)
{
	int i = 0;
	int count =0;

    //dsd i - 0? : )
	for(i = 0; i < PLAYER_ITEM_MAX; i++)
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


bool isEqual(char *str1, char *str2)
{
    if(strcmp(str1,str2) == 0)
        return true;
    else
        return false;
}

void handleDirection(Command *c)
{
    if(isEqual(c->noun,"NORTH") == true || isEqual(c->noun,"N") == true )
        c->cmd = NORTH;
    else if(isEqual(c->noun,"SOUTH") == true || isEqual(c->noun,"S") == true )
        c->cmd = SOUTH;
    else if(isEqual(c->noun,"EAST") == true || isEqual(c->noun,"E") == true )
        c->cmd = EAST;
    else if(isEqual(c->noun,"WEST") == true || isEqual(c->noun,"W") == true )
        c->cmd = WEST;
}
