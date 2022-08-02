#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

////
_Bool getInput(void);
int action(int *room_curr_idx, int *dir_idx);
int isInput(int *dir_idx);
int list_organise();
void delay(int sec);
void pickup(int *room_curr_idx, int *dir_idx);
void drop(int *room_curr_idx, int *dir_idx);


////
char buffer_input[20];

////
struct item_info
{
    char name[40];
    int hp;
};

struct player
{
    char name[20];
    int hp;
    struct item_info inventory[5];
}p1;

struct map
{
    char desc[40];
    struct item_info item[3];
    int move[4];
}room[4];

////
int main()
{
    printf("\n      Welcome to CaveExplorer        \n");

    printf("\nPlayer Name :");
    scanf("%s",p1.name);

    printf("\nHINT:Try using the \"help\" action.\n");

    int room_curr_idx = 0;
    int dir_idx = 0;

    for(int i = 0; i<4; i++)
    {
        strcpy(room[i].desc, "You're in a big dark cave-like hall.\n");
        strcpy(p1.inventory[i].name,"");
    }
    strcpy(p1.inventory[4].name,"");

    ////room1
    strcpy(room[0].item[0].name ,"Rock");
    strcpy(room[0].item[1].name ,"Cloth Rags");
    strcpy(room[0].item[2].name ,"Stick");
    room[0].move[0] =-1;
    room[0].move[1] =1;
    room[0].move[2] =-1;
    room[0].move[3] =-1;
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

    while(getInput() == 1)
    {
        list_organise();

        if(action(&room_curr_idx,&dir_idx) == 0)
           break;

    }

    return 0;
}

_Bool getInput(void)
{
    char *pBUF = buffer_input;

    strcpy(buffer_input,"");

    printf("\n[-->");
    scanf("%s", buffer_input);

    for(int i = 0; i<strlen(buffer_input); i++)
    {
        *(pBUF+i) = tolower( *(pBUF+i) );
    }

    return (1);
}

int action(int *room_curr_idx, int *dir_idx)
{
    if(strcmp(buffer_input,"")==0 || buffer_input == NULL )
    {
        return 1;
    }

    else if(strcmp(buffer_input,"quit")==0 )
    {
        printf("\n  HASTA LA VISTA ! \n");
        return 0;
    }

    else if(strcmp(buffer_input,"pickup")==0 )
    {
        pickup(room_curr_idx, dir_idx);
        return 1;
    }

    else if(strcmp(buffer_input,"drop")==0 )
    {
        drop(room_curr_idx, dir_idx);
        return 1;
    }

    else if(strcmp(buffer_input,"inventory")==0 )
    {
        for(int j=0; j<5;j++)
        {
            printf("\n%d.%s\n", j+1 , p1.inventory[j].name);
        }
        return 1;
    }

    else if(strcmp(buffer_input,"help")==0 )
    {
        printf("\nSearch the rooms for your desired treasure but beware of the UNKNOWN!....\n");
        printf("\n\"north\" : moves in the north direction");
        printf("\n\"south\" : moves in the south direction");
        printf("\n\"east\" : moves in the east direction");
        printf("\n\"west\" : moves in the west direction");
        printf("\n\"search\" : searches the room");
        printf("\n\"pickup\" : opens the pickup menu");
        printf("\n\"drop\" : opens the pickup menu\n");

        return 1;
    }

    else if(strcmp(buffer_input,"search")==0)
    {
        printf("\n%s\n", room[*room_curr_idx].desc);

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
            printf("\n %s\n", room[*room_curr_idx].item[i].name);
        }
    }

    else if(isInput(dir_idx) == 1 )
    {
        if(room[*room_curr_idx].move[*dir_idx] != (-1))
        {
            *room_curr_idx = room[*room_curr_idx].move[*dir_idx];
            printf("\nYou're now in room \"%d\"\n", (*room_curr_idx)+1);
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

int isInput(int *dir_idx)
{
    const int NORTH_INDEX = 0;
    const int SOUTH_INDEX = 1;
    const int EAST_INDEX = 2;
    const int WEST_INDEX = 3;

    if(strcmp(buffer_input,"north")==0 )
    {
        *dir_idx = NORTH_INDEX;
    }
    else if(strcmp(buffer_input,"south")==0 )
    {
        *dir_idx = SOUTH_INDEX;
    }
    else if(strcmp(buffer_input,"east")==0 )
    {
        *dir_idx = EAST_INDEX;
    }
    else if(strcmp(buffer_input,"west")==0 )
    {
        *dir_idx = WEST_INDEX;
    }
    return 1;
}


void pickup(int *room_curr_idx, int *dir_idx)
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
        printf("\n%d.%s\n", i+1,room[*room_curr_idx].item[i].name);
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
        else if(strcmp(room[*room_curr_idx].item[item_idx].name,"") == 0)
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
                    strcpy(p1.inventory[i].name,room[*room_curr_idx].item[item_idx].name);

                    printf("\nPicked up %s.\n", p1.inventory[i].name);

                    strcpy(room[*room_curr_idx].item[item_idx].name,"");

                    break;
                }
            }

            if(strcmp(p1.inventory[4].name,"") == 1)
            {
                printf("Inventory is full.");
                break;
            }

            continue;
        }
    }

}

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

void drop(int *room_curr_idx, int *dir_idx)
{
    int i = 0;
    int item_idx;

    for(i = 0; i< 5; i++)
    {
        printf("\n%d.%s\n", i+1,p1.inventory[i].name);
    }

    printf("\nType \"0\" to stop dropping up items.\n");

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
            printf("Please select from the given items to drop.\n");
            continue;
        }

        else
        {
            for(i = 0; i<5; i++)
            {
                if(strcmp(room[*room_curr_idx].item[i].name,"") == 0)
                {
                    strcpy(room[*room_curr_idx].item[i].name,p1.inventory[item_idx].name);

                    printf("\nDropped %s.\n", room[*room_curr_idx].item[i].name);

                    strcpy(p1.inventory[item_idx].name,"");

                    break;
                }

            }
            if(strcmp(room[*room_curr_idx].item[2].name,"") != 0 || strcmp(room[*room_curr_idx].item[2].name,"") != 0)
            {
                printf("Cannot drop more items in this room.");
                break;
            }

        }
    }

}

void delay(int sec)
{
    int milliSec = 1000 * sec;

    clock_t startTime = clock();

    while (clock() < startTime + milliSec)
        ;
}

