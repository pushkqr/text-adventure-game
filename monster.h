#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include "userTypes.h"
#include "player.h"

bool monsterAttack(Monster *monsterPtr, Player *playerPtr);

void monsterInit(Monster *monsterPtr);


#endif // MONSTER_H_INCLUDED
