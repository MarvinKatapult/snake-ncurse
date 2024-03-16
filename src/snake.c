#include <snake.h>
#include <stdlib.h>

Snake * newsnake( int p_start_parts ) {
    
    Snake * new_snake = malloc( sizeof( Snake ) );
    new_snake->head = NULL;
    new_snake->tail = NULL;
    new_snake->direction = 0;
    // Add Bodyparts
    for ( int i = 0; i < p_start_parts; i++ ) {
        bool is_head = i == 0;
        addSnakePart( new_snake, is_head ); 
    }

    return new_snake;
}

SnakePart * newsnakepart( int p_x, int p_y, bool p_is_head ) {
    SnakePart * new_snake_part = malloc( sizeof( SnakePart ) );
    new_snake_part->x = p_x;
    new_snake_part->y = p_y;
    new_snake_part->is_head = p_is_head;
    new_snake_part->new_part = true;
    new_snake_part->next = NULL;

    return new_snake_part;
}

void addSnakePart( Snake * p_snake, bool p_is_head ) {
    const int start_x = p_snake->tail == NULL ? 0 : p_snake->tail->x;
    const int start_y = p_snake->tail == NULL ? 0 : p_snake->tail->y;

    // Create new Body and link
    SnakePart * new_part = newsnakepart( start_x, start_y, p_is_head );
    if ( p_snake->head == NULL )  p_snake->head = new_part;
    if ( p_snake ->tail != NULL ) p_snake->tail->next = new_part;
    p_snake->tail = new_part;
}
