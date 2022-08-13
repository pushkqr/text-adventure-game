#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monster.h"
#include "player.h"

//////////////////////////////////////////////////////////////////////////
//returns true[1] only when the player is dead else false[0]
//////////////////////////////////////////////////////////////////////////

_Bool monsterAttack(monster *pMonster, player *pPlayer)
{		
	if(pPlayer->hps != 0)
		{
			pPlayer->hps -= 10;
				if(pPlayer->hps != 0)
				{
					printf("\nYou took [%d] damage.\n", 10);
					return 0;		
				}
				else
				{	
					printf("\nYou died.\n");
					return 1;
				}
		}
		else
		{	
			printf("\nYou died.\n");
			return 1;
		}
	}
		
}

