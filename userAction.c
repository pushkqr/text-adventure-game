#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mazeMap.h"
#include "userActionMove.h"
#include "relicCheck.h"

void userActionHelp(void);
int userActionQuit(char *consoleInput);
void userActionInfo(char *consoleInput);

int userAction(char *consoleInput,int *pUserLocation, const int mazeSize, const int relicLocation)
{

    if(consoleInput != NULL && strcmp(consoleInput,"quit")==0)
    {
        userActionQuit(consoleInput);
    }
    else if (consoleInput != NULL && strcmp(consoleInput,"room1.info")==0)
    {
        userActionInfo(consoleInput);
        return 1;
    }
    else if (consoleInput != NULL && strcmp(consoleInput,"room2.info")==0)
    {
        userActionInfo(consoleInput);
        return 1;
    }
    else if(consoleInput != NULL && strcmp(consoleInput,"help")==0)
    {
        userActionHelp();
        return 1;
    }
    else if(consoleInput != NULL && (strcmp(consoleInput,"north")==0 || strcmp(consoleInput,"south")==0 || strcmp(consoleInput,"east")==0 || strcmp(consoleInput,"west")==0) )
    {
        if(userActionMove(consoleInput, pUserLocation, mazeSize, relicLocation) != 0)
	{        
		return 1;
	}
	else
	{
		free(consoleInput);	
		return 0;
	}
    }
    else
    {
        printf("Can't go to %s right now...\n", consoleInput);
        return 1;
    }

}

void userActionHelp(void)
{
    printf("\n\"north\" : moves in the north direction");
    printf("\n\"south\" : moves in the south direction");
    printf("\n\"east\" : moves in the east direction");
    printf("\n\"west\" : moves in the west direction");
    printf("\n\"room1.info\" : info on room 1.");
    printf("\n\"room2.info\" : info on room 2.\n");
}


int userActionQuit(char *consoleInput)
{
    printf("\n  HASTA LA VISTA ! \n");
    free(consoleInput);
    return 0;
}

void userActionInfo(char *consoleInput)
{
    if(strcmp(consoleInput,"room1.info")== 0)
        printf("Room1 : DARKKKKKKK");

    if(strcmp(consoleInput,"room2.info")== 0)
        printf("Room2 : DARKKKKKKK");
}
