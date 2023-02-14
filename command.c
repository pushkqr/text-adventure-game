#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "command.h"

void handleCommandHelp(void)
{
        printf("\nSearch the rooms for your desired treasure but beware of the UNKNOWN!....\n");
        printf("\n\"move [DIRECTION]\" - moves in specific direction\n");
        printf("\n\"look\" : looks around\n");
        printf("\n\"pickup [ITEM_NAME]\" : opens up the item pickup menu\n");
        printf("\n\"drop [ITEM_NAME]\" : opens up the item drop menu\n");
        printf("\n\"[Inventory]/[inv]\" : shows player inventory.\n");
        printf("\n\"quit\" : procedes to quit the game\n");
}

bool handleCommandAttack(Player *playerPtr, Room *roomPtr, Command *c)
{
    int i = 0;
    int count = 0;

    for(i = 0; i <= MONSTER_COUNT_MAX;i++)
    {

       if(strcmp(roomPtr->monster_list[i].monsterName, c->noun) != 0)
        {
            if(count == MONSTER_COUNT_MAX)
            {
                printf("\nInvalid Choice.\n");
            }
            count++;
        }
        else
        {
            if(strcmp(c->noun,"") == 0 || strcmp(c->noun," ") == 0)
            {
                printf("\nIncomplete Action\n");
                break;
            }
            else if(strcmp(roomPtr->monster_list[i].monsterName, c->noun) == 0)
            {
                if(playerAttack(&(roomPtr->monster_list[i]), playerPtr) == true)
                {
                    return true;
                }
                else
                {
                    return false;
                }

            }


        }

    }

    count = 0;

    return false;

}
