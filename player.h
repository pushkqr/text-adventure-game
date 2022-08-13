#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

typedef struct 
{
    int hps;
    int room_curr_idx;
}player;

_Bool playerAttack(monster *pMonster, player *pPlayer);

#endif //PLAYER_H_INCLUDED
