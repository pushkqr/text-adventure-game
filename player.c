#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monster.h"
#include "player.h"

//////////////////////////////////////////////////////////////////////////
//returns true[1] only when the monster is slain else false[0]
//////////////////////////////////////////////////////////////////////////
_Bool playerAttack(monster *pMonster, player *pPlayer)
{
	if(pPlayer->room_curr_idx != pMonster->monster_idx)
	{
		printf("\nNothing to attack in here.\n");
		return 0;
	}	
	else 
	{
		if(pMonster->hps != 0)
		{
			pMonster->hps -= 10;
				if(pMonster->hps != 0)
				{
					printf("\nThe [%s] took [%d] damage.\n", pMonster->monsterName, 10);
					return 0;		
				}
				else
				{	
					printf("\nThe [%s] was slain\n", pMonster->monsterName);
					return 1;
				}
		}
		else
		{	
			printf("\nThe [%s] was slain\n", pMonster->monsterName);
			return 1;
		}
	}
		
}


