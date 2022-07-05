#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userAction.h"
#include "mazeMap.h"

char *consoleInput;
_Bool getInput();


int main()
{
    printf("\n      Welcome to CaveExplorer: MAZE EDITION!        \n");
    int userLocation = mazeMap();
    int *pUserLocation = NULL;
    pUserLocation = &userLocation;

    while(getInput() == 1)
    {
        if(userAction(consoleInput,pUserLocation) == 0)
        {
          break;
        }
    }

    return 0;
}

_Bool getInput()
{
    char substitute[10];

    printf("\n[-->");
    scanf("%s", substitute);

    consoleInput = (char*)calloc(strlen(substitute),sizeof(char));
    strcpy(consoleInput,substitute);

    return 1;
}
