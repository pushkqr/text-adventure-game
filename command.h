#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

void getCommand(void);
void assignEnumCmd(void);

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
    char buffer[20];

};

typedef struct Command Command;

#endif
