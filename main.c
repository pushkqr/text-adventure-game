#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "action.h"
#include "actionMove.h"
#include "mapDimensions.h"
#include "checkUser.h"
#include "posRestrict.h"

char *consoleInput;
_Bool getInput();


int main()
{
    printf("\n      Welcome to CaveExplorer: MAZE EDITION!        \n");

    const int mapSize = mapDimensions();
    int userPos = mapSize / 2;

    int *pUserPos = NULL;
    pUserPos = &userPos;

    const int relicPos = rand() % 9;
    printf("%d\n", relicPos);

    while(getInput() == 1 )
    {
        if(action(consoleInput,pUserPos,mapSize,relicPos) == 0 )
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
