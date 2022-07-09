#include <stdio.h>
#include "checkUser.h"

int checkUser(int *pUserPos, char *consoleInput, const int relicPos)
{

	if(*pUserPos == relicPos)
	{
	    	printf("\n	Voila! You hit the Jackpot\n");
	    	return 1;
		//printf("Rush to the exit before the Relic Guardian catches you!\n");
	}
	else
	{
		return 0;
	}

}
