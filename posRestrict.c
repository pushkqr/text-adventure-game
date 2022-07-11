#include <stdio.h>
#include "posRestrict.h"

int posRestrict(const int mapSize,int *pUserPos)
{

	if(*pUserPos < 1 || mapSize < *pUserPos )
	{
	        printf("The passage ahead is blocked by debris .....\n");
	        return (-1);
	}
	else
	{
	        printf("OK.\n\n");
	        return 0;
	}
}

