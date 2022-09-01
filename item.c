#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"
///////////////////////////////////////////////////////////////////////////////////
////returns 1 when items picked up succesfully and 0 when inventory full
///////////////////////////////////////////////////////////////////////////////////
void item_pickup (Player *playerPtr, Room *roomPtr);
void item_drop (Player *playerPtr, Room *roomPtr);

void item_pickup (Player *playerPtr, Room *roomPtr)
{
    int i = 0;
    int item_idx = 0;

    for(i = 0; i< 3; i++)
    {
        printf("\n%d.%s\n", i+1,roomPtr->item_list[i].name);
    }

    printf("\nType \"0\" to stop picking up items.\n");
    
    while (1)
    {
        printf("\nWhich item(s) do you want to pickup:");
        scanf("%d", &item_idx);

        item_idx -= 1;

        if(item_idx == (-1))
        {
            break;
        }
        else if(strcmp(roomPtr->item_list[item_idx].name, "") == 0)
        {
            printf("\nNothing to pick up.\n");
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
                if(strcmp(playerPtr->inventory[i].name,"") == 0 )
                {
                    strcpy(playerPtr->inventory[i].name, roomPtr->item_list[item_idx].name);

                    printf("\nPicked up %s.\n", playerPtr->inventory[i].name);

                    strcpy(roomPtr->item_list[item_idx].name,"");

                    break;
                }
            }

            if(strcmp(playerPtr->inventory[i].name,"") == 1)
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

void item_drop (Player *playerPtr, Room *roomPtr)
{
    int i = 0;
    int item_idx;

    for(i = 0; i< 5; i++)
    {
        printf("\n%d.%s\n", i+1,playerPtr->inventory[i].name);
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
        else if(strcmp(playerPtr->inventory[item_idx].name,"") == 0)
        {
            printf("\nNothing is there to drop .\n");
            continue;
        }
        else if(item_idx > 4 || item_idx < 0)
        {
            printf("\nInvalid Choice.\n");
            continue;
        }
        else
        {
            for(i =0; i<3; i++)
            {
                if(strcmp(roomPtr->item_list[i].name,"") == 0 )
                {
                    strcpy(roomPtr->item_list[i].name, playerPtr->inventory[item_idx].name);

                    printf("\nDropped %s.\n", roomPtr->item_list[i].name);

                    strcpy(playerPtr->inventory[item_idx].name,"");

                    break;
                }
            }

            if(strcmp(roomPtr->item_list[i].name,"") == 1)
            {
                printf("\nNo other items can be dropped\n");
                break;
            }

        }

        
    }

}
