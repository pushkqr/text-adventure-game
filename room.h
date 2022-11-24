#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include "userTypes.h"
#define MONSTER_COUNT_MAX 3
#define ROOM_ITEM_MAX 3

typedef struct {
    char desc[40];
    int exits[4];
    Monster monster_list[MONSTER_COUNT_MAX];
    Item item_list[ROOM_ITEM_MAX];
} Room;

int roomInIt(Room *room);
_Bool roomExitVerify(Room *room);

#endif //ROOM_H_INCLUDED
