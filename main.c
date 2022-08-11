#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define room_count 4
//////////////////////////////////////////////////////////////////////////
//Function Prototypes
//////////////////////////////////////////////////////////////////////////
void getCommand(void);
void assignEnumCmd(void);
void dirMove(void);
//////////////////////////////////////////////////////////////////////////
// Global variables
//////////////////////////////////////////////////////////////////////////
int room_curr_idx;
enum EnumCommand
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
    QUIT,
    HELP,
    INVALID
};

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
struct command{

    enum EnumCommand cmd;
    char buffer[20];

}command_curr;
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
struct map
{
    char desc[40];
    int move[room_count];
}room[room_count];

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

int main()
{
    int loopBreak = 0; 
	
    printf("\n      Welcome to CaveExplorer        \n");

    printf("\nPlayer Name :");
    scanf("%19s",bufferName);
    
    printf("\nHINT:Try using the \"help\" action.\n");

	for(int i= 0;i<room_count;i++)
	{
		for(int j=0;j<4;j++)
		{
			room[i].move[j] = -1;
		}
	}

    ////room1
    room[0].move[0] = -1;
    room[0].move[1] =  1;
    room[0].move[2] = -1;
    room[0].move[3] = -1;

    ////room2
    room[1].move[0] =  0;
    room[1].move[1] = -1;
    room[1].move[2] =  2;
    room[1].move[3] =  3;

    ////room3
    room[2].move[0] = -1;
    room[2].move[1] = -1;
    room[2].move[2] = -1;
    room[2].move[3] =  1;

    ////room4
    room[3].move[0] = -1;
    room[3].move[1] = -1;
    room[3].move[2] =  1;
    room[3].move[3] = -1;

	for(int i= 0;i<room_count;i++)
	{
		int count = 0;
		
		for(int j=0;j<4;j++)
		{
			if(room[i].move[j] == -1)
			{
				count++;
			}
		}
		if(count == 4)
		{
				fprintf(stderr,"Error loading the map.\n");
				exit(0);
		}

	}
/*
    while(loopBreak != (-1))
    {
        getCommand();

        printf("\nYou are currently in room [%d].\n", room_curr_idx+1);

        switch(command_curr.cmd)
        {
            case NORTH:
            case SOUTH:
            case EAST:
            case WEST:
                dirMove();
                break;
            case HELP:
                printf("\nSearch the rooms for your desired treasure but beware of the UNKNOWN!....\n");
                printf("\n\"north\" : moves in the north direction");
                printf("\n\"south\" : moves in the south direction");
                printf("\n\"east\" : moves in the east direction");
                printf("\n\"west\" : moves in the west direction");
                printf("\n\"quit\" : procedes to quit the game");
                break;
            case QUIT:
                printf("\nBye!\n");
                loop_break = -1;
                break;
            case INVALID:
                printf("\nCannot understand the command [%s].\n", command_curr.buffer);
                break;

        }
    }
*/
    return 0;
}
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void getCommand()
{
    char *p = command_curr.buffer;

    strcpy(command_curr.buffer,"");

    printf("\n[-->");
    scanf("%19s", command_curr.buffer);

    for(int i = 0; i<strlen(command_curr.buffer); i++)
    {
        *(p+i) = toupper( *(p+i) );
    }

    assignEnumCmd();

}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

void assignEnumCmd(void)
{
    if(strcmp(command_curr.buffer,"NORTH")==0)
        command_curr.cmd = NORTH;
    else if(strcmp(command_curr.buffer,"SOUTH")==0)
        command_curr.cmd = SOUTH;
    else if(strcmp(command_curr.buffer,"EAST")==0)
        command_curr.cmd = EAST;
    else if(strcmp(command_curr.buffer,"WEST")==0)
        command_curr.cmd = WEST;
    else if(strcmp(command_curr.buffer,"QUIT")==0)
        command_curr.cmd = QUIT;
    else if(strcmp(command_curr.buffer,"HELP")==0)
        command_curr.cmd = HELP;
    else
        command_curr.cmd = INVALID;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

void dirMove(void)
{
    if(command_curr.cmd >= 0 && command_curr.cmd < 4)
    {
        if(room[room_curr_idx].move[command_curr.cmd] != (-1))
        {
            room_curr_idx = room[room_curr_idx].move[command_curr.cmd];
        }
        else
        {
            printf("\nCan't go to %s right now...\n", command_curr.buffer);
        }
    }

}
