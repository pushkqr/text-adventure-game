#include <stdio.h>

#include "posRestrict.h"


int posRestrict(int size,int *pUserPos)
{

	if(*pUserPos < 1 || size < *pUserPos )
	{
	        printf("\nThe passage ahead is blocked by debris .....\n");
	        return (1);
	}
	else
	{
        return 0;
	}

}
