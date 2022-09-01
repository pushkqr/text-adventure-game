#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "monster.h"
#include "player.h"

//////////////////////////////////////////////////////////////////////////
//returns true[1] only when the monster is slain else false[0]
//////////////////////////////////////////////////////////////////////////
_Bool playerAttack(Monster *monsterPtr, Player *playerPtr)
{
	int attack_rand_player = rand() % 3;
	printf("dice %d\n", attack_rand_player);

	if (strcmp(monsterPtr->monsterName, "") == 0)
	{
		printf("\nNothing to attack in here.\n");
		return 0;
	}	
	else 
	{
		if(monsterPtr->hps > 0 && attack_rand_player == 0)
		{
				if(monsterPtr->hps < 0)
				{
					printf("\nYou missed.\n");
					return 0;		
				}
		}
		else if(monsterPtr->hps > 0 && attack_rand_player == 1)
		{
				monsterPtr->hps -= 10;
				printf("\nThe [%s] took [%d] damage.\n", monsterPtr->monsterName, 10);

				if (monsterPtr->hps > 0)
					return 0;		
				else
				{		
					printf("\nThe [%s] was slain\n", monsterPtr->monsterName);
					strcpy(monsterPtr->monsterName, "");
					return 1;
				}
		}
		else if(monsterPtr->hps > 0 && attack_rand_player == 2)
		{
			monsterPtr->hps -= 2 * 10;
			printf("\nThe [%s] took [%d] damage.\n", monsterPtr->monsterName, 10);

			if (monsterPtr->hps > 0)
				return 0;		
			else
			{		
				printf("\nThe [%s] was slain\n", monsterPtr->monsterName);
				strcpy(monsterPtr->monsterName, "");
				return 1;
			}
		}
		
		
	}
		
}


