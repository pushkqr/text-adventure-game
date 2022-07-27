#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "actionMove.h"
#include "posRestrict.h"

#define N "north"
#define W "west"
#define E "east"
#define S "south"

int actionMove(char *consoleInput,int *pUserPos, int size, int *relicPos )
{
	if(strcmp(consoleInput,N)==0)
	{
	        if(*pUserPos > 3)
                *pUserPos  -= 3;
            else
            {
                printf("\nCan't go north right now\n");
                return 1;
            }

	        if(posRestrict(size, pUserPos)== (0))
	        {
	            printf("\nYou're now in room \"%d\"", *pUserPos);
                return 1;
	        }
            else
            {
                *pUserPos  -= 3;
                return 1;
            }

    }
	else if(strcmp(consoleInput,S)==0)
	{
            *pUserPos  += 3;

            if(posRestrict(size, pUserPos)== (0))
	        {
	            printf("\nYou're now in room \"%d\"", *pUserPos);
                return 1;
	        }
            else
            {
                *pUserPos  -= 3;
                return 1;
            }

    }
	else if(strcmp(consoleInput,E)==0)
	{
	        *pUserPos  += 1;

	        if(posRestrict(size, pUserPos)== (0))
	        {
	            printf("\nYou're now in room \"%d\"", *pUserPos);
                return 1;
	        }
            else
            {
                *pUserPos  += 1;
                return 1;
            }

	}
	else if(strcmp(consoleInput,W)==0)
	{
	        *pUserPos  -= 1;

	        if(posRestrict(size, pUserPos)== (0))
	        {
	            printf("\nYou're now in room \"%d\"", *pUserPos);
                return 1;
	        }
            else
            {
                *pUserPos  += 1;
                return 1;
            }

	}

}



