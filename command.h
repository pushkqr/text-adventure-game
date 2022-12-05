#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

enum EnumCommand
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
    QUIT,
    HELP,
    ATTACK,
    PICKUP,
    DROP,
    LOOK,
    INVENTORY,
    INVALID
};

struct Command{

    enum EnumCommand cmd;
    char buffer[30];
    char verb[20];
    char noun[20];

};

typedef struct Command Command;


void getCommand(void);
void assignEnumCmd(Command *tempCmd);
void handleCommandHelp(void);

#endif
