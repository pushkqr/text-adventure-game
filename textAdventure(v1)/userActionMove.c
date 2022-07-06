#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mazeMap.h"
#include "positionBoundaries.h"

void userActionMove(char *consoleInput,int *pUserLocation, const int mazeSize)
{
		
	if(consoleInput!=NULL && strcmp(consoleInput,"north")==0)
	{
	        *pUserLocation  -= 3;
	        if(positionBoundaries(mazeSize, pUserLocation)!= (-1))
	        {
	            printf("You're now in room \"%d\"", *pUserLocation);
	        }
	    }
	else if(consoleInput!=NULL && strcmp(consoleInput,"south")==0)
	{
	        *pUserLocation  += 3;
	        if(positionBoundaries(mazeSize, pUserLocation) != (-1))
	        {
	            printf("You're now in room \"%d\"", *pUserLocation);
	        }
	    }
	else if(consoleInput!=NULL && strcmp(consoleInput,"east")==0)
	{
	        *pUserLocation  += 1;
	        if(positionBoundaries(mazeSize, pUserLocation) != (-1))
	        {
	            printf("You're now in room \"%d\"", *pUserLocation);
	        }
	}	
	else if(consoleInput!=NULL && strcmp(consoleInput,"west")==0)
	{
	        *pUserLocation  -= 1;
	        if(positionBoundaries(mazeSize, pUserLocation) != (-1))
	        {
	            printf("You're now in room \"%d\"", *pUserLocation);
	        }
	}

}



