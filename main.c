#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n "north"
#define w "west"
#define e "east"
#define s "south"

_Bool getInput(void);
char *consoleInput;
int action(int *index);

struct map
{
    char desc[40];
    char list[15][15];
    int move[4];
}room[4];

int main()
{
    int index = 0;

    for(int i = 0; i<4; i++)
    {
        strcpy(room[i].desc, "You're in a big dark cave-like hall.\n");
    }


    ////room1
    strcpy(room[0].list[0] ,"Rock x2");
    strcpy(room[0].list[1] ,"Cloth Rags x1");
    strcpy(room[0].list[2] ,"Stick x1");
    room[0].move[0] =-1;
    room[0].move[1] =1;
    room[0].move[2] =-1;
    room[0].move[3] =-1;
    ////room2
    strcpy(room[1].list[0] ,"Necklace x1");
    strcpy(room[1].list[1] ,"Rusted Pole x1");
    strcpy(room[1].list[2] ,"Stick x1");
    room[1].move[0] =0;
    room[1].move[1] =-1;
    room[1].move[2] =2;
    room[1].move[3] =3;
    ////room3
    strcpy(room[2].list[0] ,"Rock x1");
    strcpy(room[2].list[1] ,"Skull x1");
    strcpy(room[2].list[2] ,"Sharp Stick x1");
    room[2].move[0] =-1;
    room[2].move[1] =-1;
    room[2].move[2] =-1;
    room[2].move[3] =1;
    ////room4
    strcpy(room[3].list[0] ,"Rock x1");
    strcpy(room[3].list[1] ,"Jacket x1");
    strcpy(room[3].list[2] ,"Empty Sack x1");
    room[3].move[0] =-1;
    room[3].move[1] =-1;
    room[3].move[2] =1;
    room[3].move[3] =-1;


    while(getInput() == 1)
    {
        if(action(&index) == 0)
            break;
    }

    return 0;
}

_Bool getInput(void)
{
    char substitute[10];

    printf("\n[-->");
    scanf("%s", substitute);

    consoleInput = (char*) malloc(strlen(substitute) * sizeof(char));
    strcpy(consoleInput,substitute);

    return (1);
}

int action(int *index)
{
    if(consoleInput != NULL && (strcmp(consoleInput,"quit")==0 || strcmp(consoleInput,"QUIT")==0))
    {
        printf("\n  HASTA LA VISTA ! \n");
        free(consoleInput);
        return 0;

    }

    else if(consoleInput != NULL && (strcmp(consoleInput,"help")==0 || strcmp(consoleInput,"HELP")==0))
    {
        printf("\nSearch the rooms for your desired treasure but beware of the UNKNOWN!....\n");
        printf("\n\"north\" : moves in the north direction");
        printf("\n\"south\" : moves in the south direction");
        printf("\n\"east\" : moves in the east direction");
        printf("\n\"west\" : moves in the west direction");
        printf("\n\"search\" : searches the room");
        printf("\n\"look\" : gives a brief description of the room");
        printf("\n\nHINT:Type actions keeping the case in mind\n");

        return 1;
    }

    else if(consoleInput != NULL && ( strcmp(consoleInput,"search")==0 || strcmp(consoleInput,"SEARCH")==0))
    {
        for(int i = 0; i< 3; i++)
        {
            printf("\n  %s\n", room[*index].list[i]);
        }
    }

    else if(consoleInput != NULL && (strcmp(consoleInput,"look")==0 || strcmp(consoleInput,"LOOK")==0))
    {
        printf("\n%s\n", room[*index].desc);
    }

    else if(consoleInput != NULL && (strcmp(consoleInput,n)==0) )
    {
        if(room[*index].move[0] != (-1))
        {
            *index = room[*index].move[0];
            printf("\nYou're now in room \"%d\"\n", (*index)+1);

        }
        else
        {
            printf("\nCan't travel north right now.\n");
        }
    }

    else if(consoleInput != NULL && (strcmp(consoleInput,s)==0) )
    {
        if(room[*index].move[1] != (-1))
        {
            *index = room[*index].move[1];
            printf("\nYou're now in room \"%d\"\n", (*index)+1);
        }
        else
        {
            printf("\nCan't travel south right now.\n");
        }
    }

    else if(consoleInput != NULL && (strcmp(consoleInput,e)==0) )
    {
        if(room[*index].move[2] != (-1))
        {
            *index = room[*index].move[2];
            printf("\nYou're now in room \"%d\"\n", (*index)+1);
        }
        else
        {
            printf("\nCan't travel east right now.\n");
        }
    }

    else if(consoleInput != NULL && (strcmp(consoleInput,w)==0) )
    {
        if(room[*index].move[3] != (-1))
        {
            *index = room[*index].move[3];
            printf("\nYou're now in room \"%d\"\n", (*index)+1);
        }
        else
        {
            printf("\nCan't travel west right now.\n");
        }
    }

    else
    {
        printf("\nCan't go to %s right now...\n", consoleInput);
        return 1;
    }

}
