#ifndef __GAME_H__
#define __GAME_H__
#include <stdbool.h>
typedef struct _snake Snake;
typedef struct _snake_food SnakeFood;

typedef struct _win_st WINDOW;

void startGame( void );

void startGameLoop( WINDOW * board );

int getSnakeInput( WINDOW * board, Snake * snake );
void moveSnake( WINDOW * board, Snake * snake );

void drawSnake( WINDOW * board, Snake * snake );

void checkFoodCollision( SnakeFood * food, Snake * snake );
void newFoodLocation( SnakeFood * food, Snake * snake );
void drawFood( WINDOW * board, SnakeFood * food );

bool gameLost( Snake * snake );

#endif // __GAME_H__
