
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "item.h"


#define ITEM_COUNT_MAX 3

///////////////////////////////////////////////////////////////////////////////////
////
///////////////////////////////////////////////////////////////////////////////////
bool isInventoryFull(Player *playerPtr);
bool isRoomFull(Room *roomPtr);


//dsd interesting - not sure i would put handlitempuckup here (in item)
//      its more of a thing the player does than the item does
//      better in main with th other commands
//dsd variable names need to diff then function names
//      function name - lowerUpperUpper - handleItemPickup
//      varuabel name - lower_lower     - player_ptr
void handleCommandPickup (Player *playerPtr, Room *roomPtr, Command *c)
{
    int i = 0;
    //dsd int j = 0; unused
    int count = 0;
   // bool is_over;
    //char pickup_item[20];

    //dsd is_over was never getting intilized
    //is_over = false;

    //dsd wierd ass indent?! :)

    for(i = 0; i <= ITEM_COUNT_MAX;i++)
    {

       if(strcmp(roomPtr->item_list[i].name, c->noun) != 0)
        {

            if(count == ITEM_COUNT_MAX)
            {

                printf("\nInvalid Choice.\n");
            }
            count++;

        }
        else
        {

            if(isInventoryFull(playerPtr) == true)
            {

                printf("\nInventory full.\n");
               // is_over = true;
                break;
            }
            else if(strcmp(c->noun,"") == 0 || strcmp(c->noun," ") == 0)
            {
                printf("\nIncomplete Action\n");
                break;
            }
            else if(strcmp(roomPtr->item_list[i].name, c->noun) == 0)
            {
                for(int k = 0;k<PLAYER_ITEM_MAX;k++)
                {
                    if(strcmp(playerPtr->inventory[k].name,"") == 0 )
                    {
                        strcpy(playerPtr->inventory[k].name, c->noun);
                        playerPtr->inventory[k].dps = roomPtr->item_list[i].dps;

                        printf("\nPicked up %s.\n", playerPtr->inventory[k].name);

                        strcpy(roomPtr->item_list[i].name,"");
                        roomPtr->item_list[i].dps = 0;

                        break;
                    }
                }

            }


        }


    }

    count = 0;



}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void handleCommandDrop(Player *playerPtr, Room *roomPtr, Command *c)
{
    int i = 0;
    //dsd unused int j = 0;
    int count = 0;
    //bool is_over;
    //char drop_item[20];

    //dsd
   // is_over = false;

    for(i = 0; i <= PLAYER_ITEM_MAX;i++)
    {

       if(strcmp(playerPtr->inventory[i].name, c->noun) != 0)
        {
            if(count == PLAYER_ITEM_MAX)
            {
                printf("\nInvalid Choice.\n");
            }
            count++;
        }
        else if(strcmp(c->noun,"") == 0 || strcmp(c->noun," ") == 0)
        {
            printf("\nbruh you dumb?\n");
            break;
        }
        else
        {

            if(isRoomFull(roomPtr) == true)
            {

                printf("\nThis room stuffed up bro.\n");

            }

            else if(strcmp(playerPtr->inventory[i].name, c->noun) == 0)
            {
                for(int k = 0;k<ITEM_COUNT_MAX;k++)
                {
                    if(strcmp(roomPtr->item_list[k].name,"") == 0 )
                    {
                        strcpy(roomPtr->item_list[k].name, c->noun);
                        roomPtr->item_list[k].dps = playerPtr->inventory[i].dps;

                        printf("\nDropped %s.\n", roomPtr->item_list[k].name);

                        strcpy(playerPtr->inventory[i].name,"");
                        playerPtr->inventory[i].dps = 0;

                        break;
                    }
                }

            }

        }
    }

    count = 0;

}

bool isInventoryFull(Player *playerPtr)
{
    int i = 0;
    int count = 0;

    for(i =0; i<PLAYER_ITEM_MAX;i++)
    {
        if(strcmp(playerPtr->inventory[i].name,"") != 0)
        {
            count++;
            if(count == PLAYER_ITEM_MAX)
            {
                return true;
            }
        }
    }

    return false;
}


bool isRoomFull(Room *roomPtr)
{
    int i = 0;
    int count = 0;

    for(i =0; i<ITEM_COUNT_MAX;i++)
    {
        if(strcmp(roomPtr->item_list[i].name,"") != 0)
        {
            count++;
            if(count == ITEM_COUNT_MAX)
            {
                return true;
            }
        }
    }

    return false;
}

void handleCommandEquip(Player *playerPtr, Command *c)
{
    int i = 0;
    int count = 0;

    for(i = 0; i <= PLAYER_ITEM_MAX;i++)
    {
       if(strcmp(playerPtr->inventory[i].name, c->noun) != 0)
        {
            if(count == PLAYER_ITEM_MAX)
            {
                printf("\nInvalid Choice.\n");
            }
            count++;
        }
        else if(strcmp(c->noun,"") == 0 || strcmp(c->noun," ") == 0)
        {
            printf("\nbruh you dumb?\n");
            break;
        }
        else
        {
            if(strcmp(playerPtr->inventory[i].name, c->noun) == 0)
            {
                playerPtr->active_item_idx = i;
                break;
            }

        }
    }

    count = 0;
}
