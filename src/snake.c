#include <gb/gb.h>

#include "../res/snake.h"
#include "apple.h"
#include "snake.h"

struct snake_position snake[360];
uint8_t snake_new_direction = DIRECTION_UP;
uint16_t snake_size = 0;
uint8_t snake_tiles_add = 0;

void addSnake() {
    snake_size++;
    if (1 == snake_size) {
        snake[0].x = 0;
        snake[0].y = 1;
        snake[0].direction = DIRECTION_UP;
        snake_new_direction = DIRECTION_UP;

        return;
    }

    if (360 < snake_size) {
        return;
    }

    uint8_t x = snake[snake_size -2].x;
    uint8_t y = snake[snake_size -2].y;
    switch (snake[snake_size -2].direction) {
        case DIRECTION_UP:
            y += 1;
            break;
        case DIRECTION_RIGHT:
            x -= 1;
            break;
        case DIRECTION_DOWN:
            y -= 1;
            break;
        case DIRECTION_LEFT:
            x += 1;
    }
    snake[snake_size -1].x = x;
    snake[snake_size -1].y = y;
    snake[snake_size -1].direction = snake[snake_size -2].direction;
}

void checkApple() {
    if (snake[0].x == apple_pos.x && snake[0].y == apple_pos.y) {
        snake_tiles_add += 3;
        setRandomApple();
    }
}

void drawSnake() {
    for (uint16_t index = 0; index < snake_size; index++) {
        drawSnakeTile(index);
    }
}

void drawSnakeTile(uint16_t index) {
    uint8_t tile;

    if (0 == index) {
        switch (snake[index].direction) {
            case DIRECTION_UP:
                tile = SNAKE_HEAD_UP;
                break;
            case DIRECTION_RIGHT:
                tile = SNAKE_HEAD_RIGHT;
                break;
            case DIRECTION_DOWN:
                tile = SNAKE_HEAD_DOWN;
                break;
            case DIRECTION_LEFT:
                tile = SNAKE_HEAD_LEFT;
                break;
        }
    } else if (index == snake_size - 1) {
        switch (snake[index].direction) {
            case DIRECTION_UP:
            case DIRECTION_UP_LEFT:
            case DIRECTION_UP_RIGHT:
                tile = SNAKE_TAIL_DOWN;
                break;
            case DIRECTION_RIGHT:
            case DIRECTION_RIGHT_UP:
            case DIRECTION_RIGHT_DOWN:
                tile = SNAKE_TAIL_LEFT;
                break;
            case DIRECTION_DOWN:
            case DIRECTION_DOWN_LEFT:
            case DIRECTION_DOWN_RIGHT:
                tile = SNAKE_TAIL_UP;
                break;
            case DIRECTION_LEFT:
            case DIRECTION_LEFT_DOWN:
            case DIRECTION_LEFT_UP:
                tile = SNAKE_TAIL_RIGHT;
                break;
            default:

        }
    } else {
        /*
         * The SNAKE_BODY_ definitions describe where the snake tile is
         * open to connect to another tile, for example
         * SNAKE_BODY_DOWN_RIGHT.
         * That's why it might seem count intuitive when the new
         * direction is DOWN and the old is LEFT, but that's where the
         * snake is moving to, so the open part is on the RIGHT.
         */
        switch (snake[index].direction) {
            case DIRECTION_UP:
            case DIRECTION_DOWN:
                tile = SNAKE_BODY_UP;
                break;
            case DIRECTION_RIGHT:
            case DIRECTION_LEFT:
                tile = SNAKE_BODY_RIGHT;
                break;
            case DIRECTION_DOWN_LEFT:
            case DIRECTION_RIGHT_UP:
                tile = SNAKE_BODY_DOWN_RIGHT;
                break;
            case DIRECTION_DOWN_RIGHT:
            case DIRECTION_LEFT_UP:
                tile = SNAKE_BODY_LEFT_DOWN;
                break;
            case DIRECTION_UP_RIGHT:
            case DIRECTION_LEFT_DOWN:
                tile = SNAKE_BODY_LEFT_UP;
                break;
            case DIRECTION_RIGHT_DOWN:
            case DIRECTION_UP_LEFT:
                tile = SNAKE_BODY_UP_RIGHT;
                break;
        }
    }

    set_bkg_tile_xy(snake[index].x, snake[index].y, tile);
}

void initSnake() {
    // add 3 snake tiles for the beginning
    addSnake();
    addSnake();
    addSnake();
}

void moveSnake() {
    if (0 == snake_tiles_add) {
        // we need to clear the screen on the last tile if no new
        // tiles are being added, otherwise it would stay there
        set_bkg_tile_xy(snake[snake_size -1].x, snake[snake_size -1].y, EMPTY_BACKGROUND);
    } else {
        addSnake();
        snake_tiles_add--;
    }

    // copy all positions from the back to the front to move every tile
    // forward, except for the head
    for (uint16_t i = snake_size -1; i > 0; i--) {
        snake[i].x = snake[i-1].x;
        snake[i].y = snake[i-1].y;
        snake[i].direction = snake[i-1].direction;
    }

    // move the head to the new direction
    snake[0].direction = snake_new_direction;
    switch (snake[0].direction) {
        case DIRECTION_UP:
            snake[0].y -= 1;
            break;
        case DIRECTION_RIGHT:
            snake[0].x += 1;
            break;
        case DIRECTION_DOWN:
            snake[0].y += 1;
            break;
        case DIRECTION_LEFT:
            snake[0].x -= 1;
    }
    checkApple();
}

void setSnakeDirection(uint8_t direction) {
    if (DIRECTION_RIGHT == direction && DIRECTION_UP == snake[0].direction) {
        snake[0].direction = DIRECTION_RIGHT_UP;
    } else if (DIRECTION_DOWN == direction && DIRECTION_LEFT == snake[0].direction) {
        snake[0].direction = DIRECTION_DOWN_LEFT;
    } else if (DIRECTION_DOWN == direction && DIRECTION_RIGHT == snake[0].direction) {
        snake[0].direction = DIRECTION_DOWN_RIGHT;
    } else if (DIRECTION_LEFT == direction && DIRECTION_UP == snake[0].direction) {
        snake[0].direction = DIRECTION_LEFT_UP;
    } else if (DIRECTION_UP == direction && DIRECTION_RIGHT == snake[0].direction) {
        snake[0].direction = DIRECTION_UP_RIGHT;
    } else if (DIRECTION_LEFT == direction && DIRECTION_DOWN == snake[0].direction) {
        snake[0].direction = DIRECTION_LEFT_DOWN;
    } else if (DIRECTION_UP == direction && DIRECTION_LEFT == snake[0].direction) {
        snake[0].direction = DIRECTION_UP_LEFT;
    } else if (DIRECTION_RIGHT == direction && DIRECTION_DOWN == snake[0].direction) {
        snake[0].direction = DIRECTION_RIGHT_DOWN;
    }

    snake_new_direction = direction;
}
