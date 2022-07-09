#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int relicCheck(int *pUserLocation, char *consoleInput, const int relicLocation)
{
	
	if(*pUserLocation == relicLocation)
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
