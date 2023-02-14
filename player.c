#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "monster.h"
#include "player.h"

//////////////////////////////////////////////////////////////////////////
//
// return
//     true - monster slain
//     false - monster lives!
//
//////////////////////////////////////////////////////////////////////////
bool playerAttack(Monster *monsterPtr, Player *playerPtr)
{
    int dmg_multiplier = rand() % 3;

    if(monsterPtr->hps > 0)
    {
            monsterPtr->hps -= dmg_multiplier * playerPtr->inventory[playerPtr->active_item_idx].dps;

            if(dmg_multiplier == 0)
            {
                printf("\nYou missed.\n");
                return false;
            }
            else
            {
                if(dmg_multiplier == 2)
                {
                    printf("\nCRICTICAL!\n");
                }

                printf("\nThe [%s] took [%d] damage.\n", monsterPtr->monsterName, dmg_multiplier * playerPtr->inventory[playerPtr->active_item_idx].dps);

                if(monsterPtr->hps > 0)
                {
                    monsterPtr->was_attacked = true;
                    return false;
                }
                else
                {
                    printf("\nThe [%s] was slain\n", monsterPtr->monsterName);
                    strcpy(monsterPtr->monsterName, "");
                    return true;
                }
            }
    }

    return false;

}

