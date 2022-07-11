#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "actionMove.h"
#include "checkUser.h"
#include "posRestrict.h"
#include "endCheck.h"

int actionMove(char *consoleInput,int *pUserPos, const int mapSize, const int relicPos, int monster1Pos, int monster2Pos )
{
	if(consoleInput!=NULL && strcmp(consoleInput,"north")==0)
	{
	        *pUserPos  += 4;
	        if(posRestrict(mapSize, pUserPos)!= (-1))
	        {
	            printf("You're now in room \"%d\"", *pUserPos);

                if(checkUser(pUserPos, relicPos, monster1Pos, monster2Pos) == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }

	        }

    }
	else if(consoleInput!=NULL && strcmp(consoleInput,"south")==0)
	{
	        *pUserPos  -= 4;
	        if(posRestrict(mapSize, pUserPos) != (-1) )
	        {
	            printf("You're now in room \"%d\"", *pUserPos);

                if(checkUser(pUserPos, relicPos, monster1Pos, monster2Pos) == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }

	        }

    }
	else if(consoleInput!=NULL && strcmp(consoleInput,"east")==0)
	{
	        *pUserPos  += 1;
	        if(posRestrict(mapSize, pUserPos) != (-1) )
	        {
	            printf("You're now in room \"%d\"", *pUserPos);

                if(checkUser(pUserPos, relicPos, monster1Pos, monster2Pos) == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }

	        }

	}
	else if(consoleInput!=NULL && strcmp(consoleInput,"west")==0)
	{
	        *pUserPos  -= 1;
	        if(posRestrict(mapSize, pUserPos) != (-1) )
	        {
	            printf("You're now in room \"%d\"", *pUserPos);

                if(checkUser(pUserPos, relicPos, monster1Pos, monster2Pos) == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }

	        }

	}

}



