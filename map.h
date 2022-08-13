#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#define room_count 4

typedef struct {
    char desc[40];
    int move[room_count];
}map;

#endif //MAP_H_INCLUDED
