#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void delay(int sec);
void checkUser(int *pUserPos, int *relicPos);

int actionSearch(int *pUserPos, int *relicPos, int size)
{
    int mon1 = rand() % size;
    int mon2 = rand() % size;

    *relicPos = rand() % size;

    if(mon1 == *relicPos)
        mon1 += 1;
    else if(mon2 == *relicPos)
        mon2 -= 1;

    for(int i = 0; i < 2; i++)
        {
            printf("Searching...\n");

            for (int j = 0; j < 4; j++)
            {
                delay(1000);
                printf("...\n");
            }
        }
    if(*pUserPos == *relicPos)
    {
        checkUser(pUserPos, relicPos);
        return 0;
    }
    else if(mon1 == *pUserPos || mon2 == *pUserPos)
    {
        printf("\nA SUDDEN ATTACK !\n");

        for (int j = 0; j < 4; j++)
            {
                delay(500);
                printf("..\n");
            }

        printf("\nYOU HAVE DIED\n");

        return 0;
    }
    else

        printf("\nThere seems nothing of value in here... \n");
        return 1;


}

void delay(int sec)
{
    int milliSec = 1000 * sec;

    clock_t startTime = clock();

    while (clock() < startTime + milliSec)
        ;
}

void checkUser(int *pUserPos, int *relicPos)
{
	if(*pUserPos == *relicPos)
	{
        printf("\n	Voila! You hit the Jackpot\n");
	}
}
