#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "action.h"
#include "actionMove.h"
#include "actionSearch.h"


#define n "north"
#define w "west"
#define e "east"
#define s "south"

#define N "NORTH"
#define W "WEST"
#define E "EAST"
#define S "SOUTH"

void actionHelp(void);
int actionQuit(char *consoleInput);

int action(char *consoleInput,int *pUserPos, int size, int *relicPos)
{
    if(consoleInput != NULL && (strcmp(consoleInput,"quit")==0 || strcmp(consoleInput,"QUIT")==0))
    {
        actionQuit(consoleInput);
    }
    else if(consoleInput != NULL && (strcmp(consoleInput,"help")==0 || strcmp(consoleInput,"HELP")==0))
    {
        actionHelp();
        return 1;
    }
    else if(consoleInput != NULL && ( strcmp(consoleInput,"search")==0 || strcmp(consoleInput,"SEARCH")==0))
    {
        if(actionSearch(pUserPos, relicPos, size) == 0)
            return 0;
        else
            return 1;
    }
    else if(consoleInput != NULL && (strcmp(consoleInput,N)==0 || strcmp(consoleInput,S)==0 || strcmp(consoleInput,E)==0 || strcmp(consoleInput,W)==0) )
    {
       if(actionMove(consoleInput, pUserPos, size, relicPos) != 0 )
        {
            return 1;
        }
        else
        {
            free(consoleInput);
            return 0;
        }

    }
    else if(consoleInput != NULL && (strcmp(consoleInput,n)==0 || strcmp(consoleInput,s)==0 || strcmp(consoleInput,e)==0 || strcmp(consoleInput,w)==0) )
    {
       if(actionMove(consoleInput, pUserPos, size, relicPos) != 0 )
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
    printf("\nSearch the rooms for your desired treasure but beware of the UNKNOWN!....\n");
    printf("\n\"north\" : moves in the north direction");
    printf("\n\"south\" : moves in the south direction");
    printf("\n\"east\" : moves in the east direction");
    printf("\n\"west\" : moves in the west direction");
    printf("\n\"search\" : searches the room");
    printf("\n\nHINT:Type actions keeping the case in mind\n");
}

int actionQuit(char *consoleInput)
{
    printf("\n  HASTA LA VISTA ! \n");
    free(consoleInput);
    return 0;
}

