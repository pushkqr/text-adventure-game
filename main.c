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

#include "main.h"
#include "room.h"
#include "monster.h"
#include "player.h"
#include "item.h"
#include "command.h"


void initRooms(void);
void initMonster(void);
void arrayOrganize(void);   //dsd
void handleCommandMove(void);
void handleCommandLook(void);
void handleCommandInventory(void);
bool isEqual(char *str1, char *str2);
void handleDirection(Command *c);
void updatePlayer(void);
void updateMonster(void);
void updateMonster(void);

//dsd
void delay(int sec);


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
bool is_debug = true;
bool is_game_over = false;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
int main()
{
    unsigned seed = time(0);

    srand(seed);

    printf("\n");
    printf("Welcome to CaveExplorer\n");
    printf("Use \"help\" for hints.\n");

    initRooms();
    initMonster();

    while (!is_game_over)
    {
        roomDisplay(room_curr_idx,&room_list[room_curr_idx]);

        updatePlayer();
        updateMonster();
 //       updateItems();

        if(p1.hps <= 0)
        {
            printf("\nYou were SLAIN!\n");
            is_game_over = true;
        }

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
    roomAddItem(&room_list[0], "ROCK", 5);
    roomAddItem(&room_list[0], "AWP", 30);
    roomAddItem(&room_list[0], "STICK", 5);

    ////room2
    roomAddItem(&room_list[1], "POLE", 10);
    roomAddItem(&room_list[1], "ROD", 10);
    roomAddItem(&room_list[1], "CHAIN", 10);

    ////room3
    roomAddItem(&room_list[2], "CAPE", 0);
    roomAddItem(&room_list[2], "SACK", 0);
    roomAddItem(&room_list[2], "KNIFE", 10);

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
    //dsd predeclare

    char *p = command_curr.buffer;

    strcpy(command_curr.buffer,"");
    strcpy(command_curr.verb,"");
    strcpy(command_curr.noun,"");

    printf("\n[-->");
    //dsd printf("%lu\n", sizeof(command_curr.buffer));
    //dsd printf("%lu\n", sizeof(char));
    //dsd why dividing 30 / 1?
    fgets(command_curr.buffer, sizeof(command_curr.buffer)/sizeof(char), stdin);

    //dsd si func
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


    for(i=0; i<DIR_MAX; i++)
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
			printf("\n[%s] -- [%d]dmg\n", room_list[room_curr_idx].item_list[i].name, room_list[room_curr_idx].item_list[i].dps);
    }

/*	printf("\nExits ~\n");

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

    }*/


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
			printf("\n[%s] -- [%d]dmg\n", p1.inventory[i].name, p1.inventory[i].dps);
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

void updatePlayer()         //returns true only if monster is attacked by the user else false
{

    printf("\nPlayer Hitpoints:[%d]\nActive Item: [%s]\n", p1.hps,p1.inventory[p1.active_item_idx].name);

    getCommand();


    if(isEqual(command_curr.verb, "QUIT") == true)
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
    //dsd pickup not working cuase of get?  did it used to be get (which would be nicer since its an easier command
    else if(isEqual(command_curr.verb,"PICKUP") == true)
    {
        //dsd handleCommandPickup
        handleCommandPickup(&p1, &room_list[room_curr_idx], &command_curr);
    }
    else if(isEqual(command_curr.verb, "INVENTORY") == true || isEqual(command_curr.verb, "INV") == true)
    {
        handleCommandInventory();
    }
    else if(isEqual(command_curr.verb, "DROP") == true)
    {
        //dsd handleCommandDrop
        handleCommandDrop(&p1, &room_list[room_curr_idx], &command_curr);
    }
    else if(isEqual(command_curr.verb, "ATTACK") == true)
    {
        handleCommandAttack(&p1, &room_list[room_curr_idx], &command_curr);
    }
    else if(isEqual(command_curr.verb, "EQUIP") == true)
    {
        handleCommandEquip(&p1, &command_curr);
    }
    else
    {
        printf("\nInvalid Command.\n");
        printf("Try using \"help\".\n");
    }

}
void updateMonster(void)
{
    int i = 0;

    for(i=0; i<MONSTER_COUNT_MAX; i++)
    {
        if(isEqual(room_list[room_curr_idx].monster_list[i].monsterName,"") != true)
        {
            if(room_list[room_curr_idx].monster_list[i].was_attacked == true)
            {
                if(monsterAttack(&room_list[room_curr_idx].monster_list[i], &p1) == true)
                    is_game_over = true;
            }

        }
    }

    return false;
}



