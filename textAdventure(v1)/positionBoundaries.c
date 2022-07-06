#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mazeMap.h"

int positionBoundaries(const int mazeSize,int *pUserLocation)
{
	
	if(*pUserLocation < 1 || mazeSize < *pUserLocation )
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

