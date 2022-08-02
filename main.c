#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//////////////////////////////////////////////////////////////////////////
//Function Prototypes
//////////////////////////////////////////////////////////////////////////
_Bool getInput(void);
int action();
int list_organise();
void delay(int sec);
void item_pickup();
void item_drop();
void buffer_command();

//////////////////////////////////////////////////////////////////////////
// Global variables
//////////////////////////////////////////////////////////////////////////
char buffer_input[20];
int room_curr_idx;
enum list_commands{ north, south, east, west, quit, help, search,  pickup , drop, inventory, invalid};
enum list_commands curr_command;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
struct item_info
{
    char name[40];
    int hp;
};

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
struct player
{
    char name[20];
    int hp;
    struct item_info inventory[5];
}p1;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
struct map
{
    char desc[40];
    struct item_info item[3];
    int move[4];
}room[4];

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

int main()
{
    printf("\n      Welcome to CaveExplorer        \n");

    printf("\nPlayer Name :");
    scanf("%s",p1.name);

    printf("\nHINT:Try using the \"help\" action.\n");

    ////room1
    strcpy(room[0].item[0].name ,"Rock");
    strcpy(room[0].item[1].name ,"Cloth Rags");
    strcpy(room[0].item[2].name ,"Stick");
    room[0].move[0] = -1;
    room[0].move[1] = 1;
    room[0].move[2] = -1;
    room[0].move[3] = -1;

    ////room2
    strcpy(room[1].item[0].name ,"Necklace");
    strcpy(room[1].item[1].name ,"Rusted Pole");
    strcpy(room[1].item[2].name ,"Stick");
    room[1].move[0] =0;
    room[1].move[1] =-1;
    room[1].move[2] =2;
    room[1].move[3] =3;

    ////room3
    strcpy(room[2].item[0].name ,"Rock");
    strcpy(room[2].item[1].name ,"Skull");
    strcpy(room[2].item[2].name ,"Sharp Stick");
    room[2].move[0] =-1;
    room[2].move[1] =-1;
    room[2].move[2] =-1;
    room[2].move[3] =1;

    ////room4
    strcpy(room[3].item[0].name ,"Rock");
    strcpy(room[3].item[1].name ,"Jacket");
    strcpy(room[3].item[2].name ,"Empty Sack");
    room[3].move[0] =-1;
    room[3].move[1] =-1;
    room[3].move[2] =1;
    room[3].move[3] =-1;

    for(int i = 0; i<4; i++)
    {
        strcpy(room[i].desc, "You're in a big dark cave-like hall.\n");
        strcpy(p1.inventory[i].name,"");
    }

    for(int i = 0; i<5; i++)
    {
        strcpy(p1.inventory[i].name,"");
    }

    while(getInput() == 1)
    {
        list_organise();
        buffer_command();

        if(action() == 0)
           break;

        printf("\nYou're now in room \"%d\"\n", (room_curr_idx)+1);

    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
_Bool getInput(void)
{
    char *p = buffer_input;

    strcpy(buffer_input,"");

    printf("\n[-->");
    scanf("%s", buffer_input);

    for(int i = 0; i<strlen(buffer_input); i++)
    {
        *(p+i) = tolower( *(p+i) );
    }

    return (1);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////


int action()
{
    if(strcmp(buffer_input,"")==0 || buffer_input == NULL )
    {
        return 1;
    }

    else if(curr_command == 4 )
    {
        printf("\n  HASTA LA VISTA ! \n");
        return 0;
    }

    else if(curr_command == 7)
    {
        item_pickup();
        return 1;
    }

    else if(curr_command == 8)
    {
        item_drop();
        return 1;
    }

    else if(curr_command == 9)
    {
        for(int j=0; j<5;j++)
        {
            printf("\n%d.%s\n", j+1 , p1.inventory[j].name);
        }
        return 1;
    }

    else if(curr_command == 5)
    {
        printf("\nSearch the rooms for your desired treasure but beware of the UNKNOWN!....\n");
        printf("\n\"north\" : moves in the north direction");
        printf("\n\"south\" : moves in the south direction");
        printf("\n\"east\" : moves in the east direction");
        printf("\n\"west\" : moves in the west direction");
        printf("\n\"search\" : searches the room");
        printf("\n\"pickup\" : opens the pickup menu");
        printf("\n\"drop\" : opens the drop menu\n");

        return 1;
    }

    else if(curr_command == 6)
    {
        printf("\n%s\n", room[room_curr_idx].desc);

        for(int i = 0; i < 1; i++)
        {
            printf("\nSearching...\n");

            for (int j = 0; j < 4; j++)
            {
                delay(1);
                printf(".\n");
            }
        }

        for(int i = 0; i< 3; i++)
        {
            printf("\n %s\n", room[room_curr_idx].item[i].name);
        }
    }

    else if(curr_command >= 0 && curr_command < 4)
    {
        if(room[room_curr_idx].move[curr_command] != (-1))
        {
            room_curr_idx = room[room_curr_idx].move[curr_command];
            return 1;
        }
        else
        {
            printf("\nCan't go to %s right now...\n", buffer_input);
            return 1;
        }
    }

    else
    {
        printf("\nCan't go to %s right now...\n", buffer_input);
        return 1;
    }

}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void item_pickup()
{
    int i = 0;
    int item_idx;

    for (int j = 0; j < 2; j++)
    {
        delay(1);
        printf(".\n");
    }

    for(i = 0; i< 3; i++)
    {
        printf("\n%d.%s\n", i+1,room[room_curr_idx].item[i].name);
    }

    printf("\nType \"0\" to stop picking up items.\n");

    while(1)
    {
        printf("\nWhich item(s) do you want to pickup:");
        scanf("%d", &item_idx);

        item_idx -= 1;

        if(item_idx == (-1))
        {
            break;
        }
        else if(strcmp(room[room_curr_idx].item[item_idx].name,"") == 0)
        {
            printf("\nNothing is there to pick up.\n");
            continue;
        }
        else if(item_idx > 2 || item_idx < 0)
        {
            printf("\nPlease select from the given items.\n");
            continue;
        }

        else
        {
            for(i =0; i<5; i++)
            {
                if(strcmp(p1.inventory[i].name,"") == 0 )
                {
                    strcpy(p1.inventory[i].name,room[room_curr_idx].item[item_idx].name);

                    printf("\nPicked up %s.\n", p1.inventory[i].name);

                    strcpy(room[room_curr_idx].item[item_idx].name,"");

                    break;
                }
            }

            if(strcmp(p1.inventory[4].name,"") == 1)
            {
                printf("\nInventory is full.\n");
                break;
            }

        }
    }

}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void item_drop()
{
    int i = 0;
    int item_idx;

    for(i = 0; i< 5; i++)
    {
        printf("\n%d.%s\n", i+1,p1.inventory[i].name);
    }

    printf("\nType \"0\" to stop dropping items.\n");

    while(1)
    {
        printf("\nWhich item(s) do you want to drop:");
        scanf("%d", &item_idx);

        item_idx -= 1;

        if(item_idx == (-1))
        {
            break;
        }
        else if(strcmp(p1.inventory[item_idx].name,"") == 0)
        {
            printf("\nNothing is there to drop .\n");
            continue;
        }
        else if(item_idx > 4 || item_idx < 0)
        {
            printf("\nPlease select from the given items to drop.\n");
            continue;
        }

        else
        {
            for(i = 0; i<5; i++)
            {
                if(strcmp(room[room_curr_idx].item[i].name,"") == 0)
                {
                    strcpy(room[room_curr_idx].item[i].name,p1.inventory[item_idx].name);

                    printf("\nDropped %s.\n", room[room_curr_idx].item[i].name);

                    strcpy(p1.inventory[item_idx].name,"");

                    break;
                }

            }
            if(strcmp(room[room_curr_idx].item[2].name,"") != 0 || strcmp(room[room_curr_idx].item[2].name,"") != 0)
            {
                printf("\nCannot drop more items in this room.\n");
                break;
            }

        }
    }

}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
int list_organise()
{
    int i = 0;
    int j = 0;

    for(i= 0; i<4; i++)
    {
        for(j=0 ;j<2; j++)
        {
            if(strcmp(room[i].item[j].name,"")==0 && strcmp(room[i].item[j+1].name,"") != 0 )
            {
                strcpy(room[i].item[j].name, room[i].item[j+1].name);

                strcpy(room[i].item[j+1].name,"");
            }

        }
    }
    for(i= 0; i<1; i++)
    {
        for(j=0 ;j<4; j++)
        {
            if(strcmp(room[i].item[j].name,"")==0 && strcmp(room[i].item[j+1].name,"") == 1 )
            {
                strcpy(room[i].item[j].name, room[i].item[j+1].name);

                strcpy(room[i].item[j+1].name,"");
            }

        }
    }
    return 0;
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
void buffer_command()
{
    if(strcmp(buffer_input,"north")==0)
        curr_command = north;
    else if(strcmp(buffer_input,"south")==0)
        curr_command = south;
    else if(strcmp(buffer_input,"east")==0)
        curr_command = east;
    else if(strcmp(buffer_input,"west")==0)
        curr_command = west;
    else if(strcmp(buffer_input,"quit")==0)
        curr_command = quit;
    else if(strcmp(buffer_input,"help")==0)
        curr_command = help;
    else if(strcmp(buffer_input,"search")==0)
        curr_command = search;
    else if(strcmp(buffer_input,"pickup")==0)
        curr_command = pickup;
    else if(strcmp(buffer_input,"drop")==0)
        curr_command = drop;
    else if(strcmp(buffer_input,"inventory")==0)
        curr_command = inventory;
    else
        curr_command = invalid;
}
