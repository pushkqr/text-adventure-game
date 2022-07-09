#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userAction.h"
#include "mazeMap.h"
#include "relicCheck.h" 

char *consoleInput;
_Bool getInput();


int main()
{
    printf("\n      Welcome to CaveExplorer: MAZE EDITION!        \n");

    const int mazeSize = mazeMap();
    int userLocation = mazeSize / 2;
    
    int *pUserLocation = NULL;
    pUserLocation = &userLocation;
	
    const int relicLocation = rand() % 9;
    printf("%d\n", relicLocation);

    while(getInput() == 1 )
    {
        if(userAction(consoleInput,pUserLocation,mazeSize,relicLocation) == 0 )
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
