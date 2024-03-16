#ifndef __SNAKE_H__
#define __SNAKE_H__
#include <stdbool.h>

typedef struct _snake Snake;
typedef struct _snake_part SnakePart;
typedef struct _snake_food SnakeFood;

typedef struct _snake {
    SnakePart * head; 
    SnakePart * tail;
    int count;
    int direction;
} Snake;

typedef struct _snake_part {
    bool is_head;
    bool new_part;
    int x, y;
    SnakePart * next;
} SnakePart;

typedef struct _snake_food {
    int x, y;
} SnakeFood;

Snake * newsnake( int start_parts );

SnakePart * newsnakepart( int x, int y, bool is_head );

void addSnakePart( Snake * snake, bool is_head );

#endif
