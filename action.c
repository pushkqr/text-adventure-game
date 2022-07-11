#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "action.h"
#include "actionMove.h"

void actionHelp(void);
int actionQuit(char *consoleInput);

int action(char *consoleInput,int *pUserPos, const int mapSize, const int relicPos)
{

    if(consoleInput != NULL && strcmp(consoleInput,"quit")==0)
    {
        actionQuit(consoleInput);
    }
    else if(consoleInput != NULL && strcmp(consoleInput,"help")==0)
    {
        actionHelp();
        return 1;
    }
    else if(consoleInput != NULL && (strcmp(consoleInput,"north")==0 || strcmp(consoleInput,"south")==0 || strcmp(consoleInput,"east")==0 || strcmp(consoleInput,"west")==0) )
    {
        if(actionMove(consoleInput, pUserPos, mapSize, relicPos) != 0 )
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

void actionHelp(void)
{
    printf("\n\"north\" : moves in the north direction");
    printf("\n\"south\" : moves in the south direction");
    printf("\n\"east\" : moves in the east direction");
    printf("\n\"west\" : moves in the west direction");
}


int actionQuit(char *consoleInput)
{
    printf("\n  HASTA LA VISTA ! \n");
    free(consoleInput);
    return 0;
}

