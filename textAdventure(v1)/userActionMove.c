#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mazeMap.h"

int positionCheckNS(char *consoleInput,int *pUserLocation);
int positionCheckWE(char *consoleInput,int *pUserLocation);

void userActionMove(char *consoleInput,int *pUserLocation)
{

   if(consoleInput!=NULL && strcmp(consoleInput,"north")==0)
    {
        *pUserLocation  -= 3;
        if(positionCheckNS(consoleInput, pUserLocation)!= (-1))
        {
            printf("You're now in room \"%d\"", *pUserLocation);
        }
    }
    else if(consoleInput!=NULL && strcmp(consoleInput,"south")==0)
    {
        *pUserLocation  += 3;
        if(positionCheckNS(consoleInput, pUserLocation) != (-1))
        {
            printf("You're now in room \"%d\"", *pUserLocation);
        }
    }
    else if(consoleInput!=NULL && strcmp(consoleInput,"east")==0)
    {
        *pUserLocation  += 1;
        if(positionCheckWE(consoleInput, pUserLocation) != (-1))
        {
            printf("You're now in room \"%d\"", *pUserLocation);
        }
    }
    else if(consoleInput!=NULL && strcmp(consoleInput,"west")==0)
    {
        *pUserLocation  -= 1;
        if(positionCheckWE(consoleInput, pUserLocation) != (-1))
        {
            printf("You're now in room \"%d\"", *pUserLocation);
        }
    }

}

int positionCheckNS(char *consoleInput,int *pUserLocation)
{
    if(consoleInput!=NULL && (*pUserLocation < 1 || *pUserLocation > (*pUserLocation * 2) ) )
    {
        printf("Cannot go any further...\n");
        return (-1);
    }
    else
    {
        printf("OK.\n\n");
        return 0;
    }
}

int positionCheckWE(char *consoleInput,int *pUserLocation)
{
     if(consoleInput!=NULL && (*pUserLocation < 1 || *pUserLocation > (*pUserLocation * 2) ) )
    {
        printf("Cannot go any further...\n");
        return (-1);
    }
    else
    {
        printf("OK.\n\n");
        return 0;
    }
}
