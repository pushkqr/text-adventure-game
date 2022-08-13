#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

typedef struct {
	char monsterName[20];
	int hps;
	int monster_idx;
}monster;

_Bool monsterAttack(monster *pMonster, player *pPlayer);

#endif //MONSTER_H_INCLUDED
