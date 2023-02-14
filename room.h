#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <stdbool.h>
#include "userTypes.h"

#define MONSTER_COUNT_MAX 3
#define ROOM_ITEM_MAX 3

enum EnumDirection
{
    DIR_NORTH,
    DIR_SOUTH,
    DIR_EAST,
    DIR_WEST,
    DIR_MAX,
};

#define NO_EXIT -1

typedef struct {
    char desc[40];
    int list_exit[DIR_MAX];
    Monster monster_list[MONSTER_COUNT_MAX];
    Item item_list[ROOM_ITEM_MAX];
} Room;


void roomInit(Room *room);
bool roomVerifyExits(Room *room, int room_idx);
void roomSetExit(Room *room, enum EnumDirection dir, int room_idx);
void roomDisplay(int room_idx, Room *room);
bool roomAddItem(Room *room, char *item, int dmg);

#endif //ROOM_H_INCLUDED
