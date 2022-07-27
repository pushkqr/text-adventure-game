#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "action.h"

int map[9];
char *consoleInput;
_Bool getInput(void);
void mapAlloc(int a);

int main()
{
    printf("\n      Welcome to CaveExplorer: MineSweeperMode!        \n");
    printf("\n\n\nHINT:Try using the \"help\" action.\n");
    int size = sizeof(map) / sizeof(int);

    mapAlloc(size);

    int *pUserPos = NULL;
    pUserPos = &map[0];

    int *relicPos = &map[8];

    while(getInput() == 1)
    {
        if(action(consoleInput, pUserPos, size, relicPos) == 0 )
            break;

    }    return 0;
}

_Bool getInput(void) {

    char substitute[10];

    printf("\n[-->");
    scanf("%s", substitute);

    consoleInput = (char*) malloc(strlen(substitute) * sizeof(char));
    strcpy(consoleInput,substitute);

    return (1);
}

void mapAlloc(int a)
{
    int roomNum = 1;

    for(int i = 0; i < a ;i++)
    {
        map[i] = roomNum;
        roomNum++;
    }
}
