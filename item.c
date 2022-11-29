
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
void item_pickup (Player *playerPtr, Room *roomPtr);
void item_drop (Player *playerPtr, Room *roomPtr);
bool isInventoryFull(Player *playerPtr);
bool isRoomFull(Room *roomPtr);

void item_pickup (Player *playerPtr, Room *roomPtr)
{
    int i = 0;
    int j = 0;
    int count = 0;
    bool is_over;
    char pickup_item[20];

    for(i = 0; i< ITEM_COUNT_MAX; i++)
    {
        if(strcmp(roomPtr->item_list[i].name,"") != 0)
        {
            printf("\n[%s]\n",roomPtr->item_list[i].name);
        }
    }

    printf("\nType \"exit\" to stop picking up items.\n");

    while (is_over != true)
    {
        printf("\nWhich item(s) do you want to pickup:");
        scanf("%s", pickup_item);


        for(i = 0; i<strlen(pickup_item); i++)
        {
            pickup_item[i] = toupper(pickup_item[i]);
        }


        for(i = 0; i <= ITEM_COUNT_MAX;i++)
        {
                if(strcmp(pickup_item,"EXIT") == 0)
                {
                    is_over = true;
                    break;
                }
               else if(strcmp(roomPtr->item_list[i].name, pickup_item) != 0)
                {
                    count++;
                    if(count == ITEM_COUNT_MAX+1)
                    {
                        printf("\nInvalid Choice.\n");
                    }
                    is_over = false;
                }
                else
                {

                    if(isInventoryFull(playerPtr) == true)
                    {

                        printf("\nInventory full.\n");
                        is_over = true;
                        break;
                    }

                    else if(strcmp(roomPtr->item_list[i].name, pickup_item) == 0)
                    {
                        for(int k = 0;k<PLAYER_ITEM_MAX;k++)
                        {
                            if(strcmp(playerPtr->inventory[k].name,"") == 0 )
                            {
                                strcpy(playerPtr->inventory[k].name, pickup_item);

                                printf("\nPicked up %s.\n", playerPtr->inventory[k].name);

                                strcpy(roomPtr->item_list[i].name,"");

                                break;
                            }
                        }

                    }


                }


            }

        count = 0;

    }

}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void item_drop(Player *playerPtr, Room *roomPtr)
{
    int i = 0;
    int j = 0;
    int count = 0;
    bool is_over;
    char drop_item[20];

    for(i = 0; i<PLAYER_ITEM_MAX; i++)
    {
        if(strcmp(playerPtr->inventory[i].name,"") != 0)
        {
            printf("\n[%s]\n",playerPtr->inventory[i].name);
        }
    }

    printf("\nType \"exit\" to stop dropping items.\n");

    while (is_over != true)
    {
        printf("\nWhich item(s) do you want to drop:");
        scanf("%s", drop_item);


        for(i = 0; i<strlen(drop_item); i++)
        {
            drop_item[i] = toupper(drop_item[i]);
        }


        for(i = 0; i <= PLAYER_ITEM_MAX;i++)
        {
                if(strcmp(drop_item,"EXIT") == 0)
                {
                    is_over = true;
                    break;
                }
               else if(strcmp(playerPtr->inventory[i].name, drop_item) != 0)
                {
                    count++;
                    if(count == PLAYER_ITEM_MAX+1)
                    {
                        printf("\nInvalid Choice.\n");
                    }
                    is_over = false;
                }
                else
                {

                    if(isRoomFull(roomPtr) == true)
                    {

                        printf("\nThis room stuffed up bro.\n");
                        is_over = true;
                        break;
                    }

                    else if(strcmp(playerPtr->inventory[i].name, drop_item) == 0)
                    {
                        for(int k = 0;k<ITEM_COUNT_MAX;k++)
                        {
                            if(strcmp(roomPtr->item_list[k].name,"") == 0 )
                            {
                                strcpy(roomPtr->item_list[k].name, drop_item);

                                printf("\nDropped %s.\n", roomPtr->item_list[k].name);

                                strcpy(playerPtr->inventory[i].name,"");

                                break;
                            }
                        }

                    }


                }


            }

        count = 0;

    }

}

/*void item_drop (Player *playerPtr, Room *roomPtr)
{
    int i = 0;
    int item_idx;

    for(i = 0; i< PLAYER_ITEM_MAX; i++)
    {
        if(strcmp(playerPtr->inventory[i].name,"") != 0)
        {
            printf("\n[%s]\n",playerPtr->inventory[i].name);
        }
    }

    printf("\nType \"0\" to stop dropping items.\n");

    while(1)
    {
        printf("\nWhich item(s) do you want to drop:");
        scanf("%1d", &item_idx);

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
                if(strcmp(roomPtr->item_list[2].name,"") != 0 )
                {
                    printf("\nNo other items can be dropped\n");
                    break;
                }
                else if(strcmp(roomPtr->item_list[i].name,"") == 0 )
                {
                    strcpy(roomPtr->item_list[i].name, playerPtr->inventory[item_idx].name);

                    printf("\nDropped %s.\n", roomPtr->item_list[i].name);

                    strcpy(playerPtr->inventory[item_idx].name,"");

                    break;
                }

            }
        }


    }

}*/

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
