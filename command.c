#include <stdio.h>
#include <string.h>

#include "command.h"

void handleCommandHelp(void)
{
        printf("\nSearch the rooms for your desired treasure but beware of the UNKNOWN!....\n");
        printf("\n\"move [DIRECTION]\" - moves in specific direction\n");
      /*  printf("\n\"(N)orth\" : moves in the north direction\n");
        printf("\n\"(S)outh\" : moves in the south direction\n");
        printf("\n\"(E)ast\" : moves in the east direction\n");
        printf("\n\"(W)est\" : moves in the west direction\n");*/
        printf("\n\"look\" : looks around\n");
        printf("\n\"pickup [ITEM_NAME]\" : opens up the item pickup menu\n");
        printf("\n\"drop [ITEM_NAME]\" : opens up the item drop menu\n");
        //printf("\n\"attack\" : attacks nearby monsters\n");
        printf("\n\"quit\" : procedes to quit the game\n");
}


/*void assignEnumCmd(Command *tempCmd)
{

    if(strcmp(tempCmd->buffer,"QUIT")==0)
        tempCmd->cmd = QUIT;
    else if(strcmp(tempCmd->buffer,"HELP")==0)
        tempCmd->cmd = HELP;
    else if(strcmp(tempCmd->buffer,"ATTACK")==0)
        tempCmd->cmd = ATTACK;
    else if(strcmp(tempCmd->buffer,"PICKUP")==0)
        tempCmd->cmd = PICKUP;
    else if(strcmp(tempCmd->buffer,"DROP")==0)
        tempCmd->cmd = DROP;
    else if(strcmp(tempCmd->buffer,"LOOK")==0)
        tempCmd->cmd = LOOK;
    else if(strcmp(tempCmd->buffer,"INVENTORY")==0)
        tempCmd->cmd = INVENTORY;
    else;
        tempCmd->cmd = INVALID
}*/
