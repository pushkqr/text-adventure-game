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
void drawMap(void);

int main()
{
    printf("\n      Welcome to CaveExplorer: MAZE EDITION!        \n");

    const int mapSize = mapDimensions();
    int userPos = 1;

    int *pUserPos = NULL;
    pUserPos = &userPos;

    const int relicPos = 17;

    while(getInput() == 1 )
    {
        int monster1Pos = rand() % mapSize;
        printf("%d", monster1Pos);
        int monster2Pos = rand() % mapSize;
        printf("%d", monster2Pos);

        drawMap();

        if(action(consoleInput, pUserPos, mapSize, relicPos, monster1Pos, monster2Pos) == 0 )
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

void drawMap(void)
{
    printf("\n                **[17]**         \n");
    printf("            /              \\  \n");
    printf("          (13)-(14)- (15)-(16)  \n");
    printf("           |  \\  |    |    |   \n");
    printf("           |  ---|----|----|        \n");
    printf("          (9)- (10)- (11)-(12)   \n");
    printf("           |  \\  |    |    |   \n");
    printf("           |  ---|----|----|        \n");
    printf("          (5) - (6)- (7) -(8)   \n");
    printf("           |  \\  |    |    |   \n");
    printf("           |  ---|----|----|        \n");
    printf("  Entry-> (1) - (2)- (3)- (4)   \n");

}
