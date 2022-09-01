#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "monster.h"
#include "player.h"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void monsterInit(Monster *monsterPtr);
//////////////////////////////////////////////////////////////////////////
// returns true[1] only when the player is dead else false[0]
//////////////////////////////////////////////////////////////////////////
_Bool monsterAttack(Monster *monsterPtr, Player *playerPtr)
{
	int attack_rand_monster = rand() % 3;

	if(strcmp(monsterPtr->monsterName, "") == 0)
	{
		return 0;
	}
	
	if(playerPtr->hps > 0 && attack_rand_monster == 0)
	{

		if(playerPtr->hps > 0)
		{
			printf("\nThe [%s] missed.\n", monsterPtr->monsterName);
			return 0;		
		}
	}
	else if(playerPtr->hps > 0 && attack_rand_monster == 1)
	{
		playerPtr->hps -= monsterPtr->dps;

		if(playerPtr->hps > 0)
		{
			printf("\nYou took [%d] damage.\n", monsterPtr->dps);
			return 0;		
		}
		else
		{		
			printf("\nYou died.\n");
			return 1;
		}
	}
	else if(playerPtr->hps > 0 && attack_rand_monster == 2)
	{
		playerPtr->hps -= (2 * monsterPtr->dps);

		if(playerPtr->hps > 0)
		{
			printf("\nYou took [%d] damage.\n", 2 * monsterPtr->dps);
			return 0;		
		}
		else
		{		
			printf("\nYou died.\n");
			return 1;
		}
	}		
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

void monsterInit(Monster *monsterPtr)
{
	strcpy(monsterPtr->monsterName, "Gremlin");
	monsterPtr->hps = 10;
	monsterPtr->dps = 5;
}