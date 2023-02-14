#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include "monster.h"
#include "player.h"
#include "room.h"

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

//dsd moved '{' to next line - either way is fine - just need to be consistent
//ie.
//Command {
//}
//or
//Command
//{
//}
//dsd will need safety length
struct Command
{
    enum EnumCommand cmd;
    char buffer[30];
    char verb[20];
    char noun[20];
};
typedef struct Command Command; //dsd nice to make a block out of struct and typedef (visually speaking)

void getCommand(void);
void assignEnumCmd(Command *tempCmd);
void handleCommandHelp(void);
bool handleCommandAttack(Player *playerPtr, Room *roomPtr, Command *c);

#endif
