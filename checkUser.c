#include <stdio.h>
#include "checkUser.h"

int checkUser(int *pUserPos, const int relicPos, int monster1Pos, int monster2Pos)
{

	if(*pUserPos == relicPos)
	{
	    	printf("\n	Voila! You hit the Jackpot\n");
	    	return 1;
		//printf("Rush to the exit before the Relic Guardian catches you!\n");
	}
	else if(*pUserPos == monster1Pos || *pUserPos == monster2Pos)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
