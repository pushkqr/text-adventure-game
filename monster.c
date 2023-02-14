#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "monster.h"
#include "player.h"

void monsterInit(Monster *monsterPtr);


//////////////////////////////////////////////////////////////////////////
// returns true[1] only when the player is dead else false[0]
//////////////////////////////////////////////////////////////////////////
bool monsterAttack(Monster *monsterPtr, Player *playerPtr)
{
    int dmg_multiplier = rand() % 3;

    if(playerPtr->hps > 0)
    {
            playerPtr->hps -= dmg_multiplier * monsterPtr->dps;

            if(dmg_multiplier == 0)
            {
                printf("\nThe [%s] missed.\n", monsterPtr->monsterName);
                return false;
            }
            else
            {
                if(dmg_multiplier == 2)
                {
                    printf("\nCRICTICAL!\n");
                }

                printf("\n[%s] attacks!.\n", monsterPtr->monsterName);

                printf("\nYou took [%d] damage.\n",dmg_multiplier * monsterPtr->dps);

            }
    }

    return false;

}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

void monsterInit(Monster *monsterPtr)
{
	strcpy(monsterPtr->monsterName, "GREMLIN");
	monsterPtr->hps = 25;
	monsterPtr->dps = 10;
	monsterPtr->was_attacked = false;
}
