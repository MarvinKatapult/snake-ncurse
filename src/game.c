#include <game.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <snake.h>

#define BOARD_SIZE  10
#define BOARD_HEIGHT BOARD_SIZE
#define BOARD_WIDTH BOARD_SIZE * 2.5

void startGame() {
    // Create MainWindow
    initscr();
    refresh();
    noecho();
    curs_set( 0 );
  
    // Get Width and Height of Mainwindow
    int screen_w, screen_h;
    getmaxyx( stdscr, screen_h, screen_w );

    // Create Boardwindow
    WINDOW * window = newwin( BOARD_HEIGHT, BOARD_WIDTH, screen_h / 2 - BOARD_HEIGHT / 2, screen_w / 2 - BOARD_WIDTH / 2 );
    keypad( window, true );
    wtimeout( window, 250 );
    box( window, 0, 0 );
    wrefresh( window );

    startGameLoop( window );

    endwin();
}

void startGameLoop( WINDOW * p_board ) {

    Snake * snake = newsnake( 1 );
    SnakeFood * food = malloc( sizeof( SnakeFood ) );
    newFoodLocation( food, snake );
    while ( !gameLost( snake ) ) {
        moveSnake( p_board, snake );
        checkFoodCollision( food, snake );

        // Clear Window
        wclear( p_board );
        box( p_board, 0, 0 );
        // Draw Snake
        drawSnake( p_board, snake );
        drawFood( p_board, food );
    }
}

int getSnakeInput( WINDOW * p_board, Snake * p_snake ) {
    chtype input = wgetch( p_board );
    if ( input == 'a' && p_snake->direction == 'd' ) return ERR; 
    if ( input == 'd' && p_snake->direction == 'a' ) return ERR; 
    if ( input == 's' && p_snake->direction == 'w' ) return ERR; 
    if ( input == 'w' && p_snake->direction == 's' ) return ERR; 
    return input;
}

void moveSnake( WINDOW * p_board, Snake * p_snake ) {

    chtype input = getSnakeInput( p_board, p_snake );

    mvwaddch( stdscr, 5, 5, input );
    SnakePart * current = p_snake->head;
    int prev_x = current->x;
    int prev_y = current->y;
    while ( current != NULL ) {
        // Save x and y
        int temp_x = current->x;
        int temp_y = current->y;

        // Move
        if ( current->is_head ) {
            if ( input == (unsigned)ERR ) input = p_snake->direction;
            p_snake->direction = input;
            switch ( input ) {
                case 'a':
                    current->x--;
                    // mvwaddch( stdscr, 5, 5, 'L' );
                    break;
                case 'd':
                    current->x++;
                    // mvwaddch( stdscr, 5, 5, 'R' );
                    break;
                case 'w':
                    current->y--;
                    // mvwaddch( stdscr, 5, 5, 'U' );
                    break;
                case 's':
                    current->y++;
                    // mvwaddch( stdscr, 5, 5, 'D' );
                    break;
            }
        } else {
            current->x = prev_x;
            current->y = prev_y;
            current->new_part = false;
        }

        prev_x = temp_x;
        prev_y = temp_y;

        // Next Element
        current = current->next;
    }
}

void drawSnake( WINDOW * p_board, Snake * p_snake ) {
    SnakePart * current = p_snake->head;
    while( current != NULL ) {
        // Draw bodypart
        mvwaddch( p_board, current->y, current->x, '#' ); 
        current = current->next;
    }
    wrefresh( p_board );
}

void checkFoodCollision( SnakeFood * p_food, Snake * p_snake ) {
    
    SnakePart * head = p_snake->head;
    if ( p_food->x == head->x && p_food->y == head->y ) {
        newFoodLocation( p_food, p_snake );
        addSnakePart( p_snake, false );
    }
}

void newFoodLocation( SnakeFood * p_food, Snake * p_snake ) {
    // Set Seed
    time_t t;
    srand( (unsigned)time( &t ) );
    int rand_x = rand() % BOARD_WIDTH;    
    int rand_y = rand() % BOARD_HEIGHT;    

    SnakePart * current = p_snake->head;
    while ( current != NULL ) {
        // Check if position is in Snake
        if ( current->x == rand_x && current->x == rand_y ) {
            newFoodLocation( p_food, p_snake );
            return;
        }
        current = current->next;
    }
    // Set New Food Position
    p_food->x = rand_x;
    p_food->y = rand_y;
}

void drawFood( WINDOW * p_board, SnakeFood * p_food ) {
    mvwaddch( p_board, p_food->y, p_food->x, 'O' );
}

bool gameLost( Snake * p_snake ) {
    SnakePart * head = p_snake->head;
    // Check for out of bounds
    if ( head->x < 0 || head->x > BOARD_WIDTH ) return true;
    if ( head->y < 0 || head->y > BOARD_HEIGHT ) return true;

    // Check for colliding bodies
    SnakePart * current = head->next;
    while ( current != NULL ) {
        if ( !current->new_part && current->x == head->x && current->y == head->y ) return true;
        current = current->next;
    }

    return false;
}
