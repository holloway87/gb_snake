#include <gb/gb.h>
#include <rand.h>

#include "../res/snake.h"
#include "apple.h"
#include "game.h"
#include "snake.h"

struct game_field_info game_field[360];
struct game_field_info *game_field_ptr = game_field;
uint8_t snake_alive = 1;
struct snake_position snake_body_first;
uint8_t snake_frames_wait = 10;
uint8_t snake_frames_left = 10;
struct snake_position snake_head;
uint8_t snake_initial_draw = 1;
struct position snake_last_position;
uint8_t snake_new_direction = DIRECTION_UP;
uint16_t snake_size = 0;
struct snake_position snake_tail;
uint8_t snake_tiles_add = 0;

void addSnake() {
    uint16_t index;

    snake_size++;
    if (1 == snake_size) {
        snake_head.x = 10;
        snake_head.y = 9;
        snake_head.direction = DIRECTION_UP;
        snake_tail.x = snake_head.x;
        snake_tail.y = snake_head.y;
        snake_tail.direction = snake_head.direction;
        snake_new_direction = snake_head.direction;
        index = snake_head.x + (snake_head.y * 20);
        game_field[index].x = snake_head.x;
        game_field[index].y = snake_head.y;
        game_field[index].direction = snake_head.direction;
        game_field[index].has_snake = 1;

        return;
    }

    if (360 < snake_size) {
        return;
    }

    uint8_t x = snake_tail.x;
    uint8_t y = snake_tail.y;
    switch (snake_tail.direction) {
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
    snake_tail.x = x;
    snake_tail.y = y;
    snake_tail.direction = snake_tail.direction;

    index = x + (y * 20);
    game_field[index].x = x;
    game_field[index].y = y;
    game_field[index].direction = snake_tail.direction;
    game_field[index].has_snake = 1;

    if (2 == snake_size) {
        snake_body_first.x = x;
        snake_body_first.y = y;
        snake_body_first.direction = snake_tail.direction;
    }
}

void checkApple() {
    if (snake_head.x == apple_pos.x && snake_head.y == apple_pos.y) {
        snake_tiles_add += 3;
        setRandomApple();
    }
}

void checkDeath() {
    game_field_ptr = game_field;
    uint16_t counter = 0;

    uint8_t x = snake_head.x;
    uint8_t y = snake_head.y;

    switch (snake_new_direction) {
        case DIRECTION_UP:
            if (0 == y) {
                y = 17;
            } else {
                y--;
            }
            break;
        case DIRECTION_RIGHT:
            if (19 == x) {
                x = 0;
            } else {
                x++;
            }
            break;
        case DIRECTION_DOWN:
            if (17 == y) {
                y = 0;
            } else {
                y++;
            }
            break;
        case DIRECTION_LEFT:
            if (0 == x) {
                x = 19;
            } else {
                x--;
            }
            break;
    }

    do {
        if (1 == game_field_ptr->has_snake && x == game_field_ptr->x && y == game_field_ptr->y) {
            snake_alive = 0;

            break;
        }

        game_field_ptr++;
        counter++;
    } while (360 > counter);
}

void drawSnake() {
    if (1 == snake_initial_draw) {
        game_field_ptr = game_field;
        uint16_t counter = 0;
        do {
            drawSnakeTile(game_field_ptr);
            game_field_ptr++;
            counter++;
        } while (360 > counter);

        snake_initial_draw = 0;

        return;
    }

    // we need to clear the screen on the last tile if no new
    // tiles are being added, otherwise it would stay there
    set_bkg_tile_xy(snake_last_position.x, snake_last_position.y, EMPTY_BACKGROUND);

    // Only draw the head, the second tile and the tail, the rest stays the same during the movement
    drawSnakeTile(&game_field[snake_head.x + (snake_head.y * 20)]);
    drawSnakeTile(&game_field[snake_body_first.x + (snake_body_first.y * 20)]);
    drawSnakeTile(&game_field[snake_tail.x + (snake_tail.y * 20)]);
}

void drawSnakeTile(struct game_field_info *game_field_index) {
    if (0 == game_field_index->has_snake) {
        set_bkg_tile_xy(game_field_index->x, game_field_index->y, EMPTY_BACKGROUND);

        return;
    }

    uint8_t tile;

    if (snake_head.x == game_field_index->x && snake_head.y == game_field_index->y) {
        switch (game_field_index->direction) {
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
    } else if (snake_tail.x == game_field_index->x && snake_tail.y == game_field_index->y) {
        switch (game_field_index->direction) {
            case DIRECTION_UP:
                tile = SNAKE_TAIL_DOWN;
                break;
            case DIRECTION_RIGHT:
                tile = SNAKE_TAIL_LEFT;
                break;
            case DIRECTION_DOWN:
                tile = SNAKE_TAIL_UP;
                break;
            case DIRECTION_LEFT:
                tile = SNAKE_TAIL_RIGHT;
                break;
        }
    } else {
        switch (game_field_index->direction) {
            case DIRECTION_UP:
            case DIRECTION_DOWN:
                tile = SNAKE_BODY_UP;
                break;
            case DIRECTION_LEFT:
            case DIRECTION_RIGHT:
                tile = SNAKE_BODY_RIGHT;
                break;
            case DIRECTION_DOWN_RIGHT:
            case DIRECTION_LEFT_UP:
                tile = SNAKE_BODY_LEFT_DOWN;
                break;
            case DIRECTION_UP_RIGHT:
            case DIRECTION_LEFT_DOWN:
                tile = SNAKE_BODY_LEFT_UP;
                break;
            case DIRECTION_RIGHT_UP:
            case DIRECTION_DOWN_LEFT:
                tile = SNAKE_BODY_DOWN_RIGHT;
                break;
            case DIRECTION_UP_LEFT:
            case DIRECTION_RIGHT_DOWN:
                tile = SNAKE_BODY_UP_RIGHT;
                break;
        }
    }

    set_bkg_tile_xy(game_field_index->x, game_field_index->y, tile);
}

uint16_t getPreviousTileIndex(struct snake_position *tile) {
    uint8_t x;
    uint8_t y;
    switch (tile->direction) {
        case DIRECTION_UP:
        case DIRECTION_RIGHT_UP:
        case DIRECTION_LEFT_UP:
            x = tile->x;
            if (0 == tile->y) {
                y = 17;
            } else {
                y = tile->y -1;
            }
            break;
        case DIRECTION_RIGHT:
        case DIRECTION_DOWN_RIGHT:
        case DIRECTION_UP_RIGHT:
            if (19 == tile->x) {
                x = 0;
            } else {
                x = tile->x +1;
            }
            y = tile->y;
            break;
        case DIRECTION_DOWN:
        case DIRECTION_RIGHT_DOWN:
        case DIRECTION_LEFT_DOWN:
            x = tile->x;
            if (17 == tile->y) {
                y = 0;
            } else {
                y = tile->y +1;
            }
            break;
        case DIRECTION_LEFT:
        case DIRECTION_UP_LEFT:
        case DIRECTION_DOWN_LEFT:
            if (0 == tile->x) {
                x = 19;
            } else {
                x = tile->x -1;
            }
            y = tile->y;
    }

    return x + (y * 20);
}

void initSnake() {
    uint16_t index;

    snake_alive = 1;
    snake_size = 0;
    snake_initial_draw = 1;

    for (uint8_t y = 0; y < 18; y++) {
        for (uint8_t x = 0; x < 20; x++) {
            index = x + (y * 20);
            game_field[index].x = x;
            game_field[index].y = y;
            game_field[index].direction = 0;
            game_field[index].has_snake = 0;
        }
    }

    // add 3 snake tiles for the beginning
    addSnake();
    addSnake();
    addSnake();
    drawSnake();

    initrand(DIV_REG);
    setRandomApple();
}

void moveSnake() {
    uint16_t index;

    if (0 == snake_tiles_add) {
        snake_last_position.x = snake_tail.x;
        snake_last_position.y = snake_tail.y;
    } else {
        addSnake();
        snake_tiles_add--;
    }

    // move the first body part
    moveSnakeTile(&snake_body_first);
    switch (snake_new_direction) {
        case DIRECTION_UP:
            switch (snake_body_first.direction) {
                case DIRECTION_LEFT:
                case DIRECTION_LEFT_UP:
                case DIRECTION_LEFT_DOWN:
                    snake_body_first.direction = DIRECTION_UP_LEFT;
                    break;
                case DIRECTION_RIGHT:
                case DIRECTION_RIGHT_UP:
                case DIRECTION_RIGHT_DOWN:
                    snake_body_first.direction = DIRECTION_UP_RIGHT;
                    break;
                case DIRECTION_UP_LEFT:
                case DIRECTION_UP_RIGHT:
                    snake_body_first.direction = DIRECTION_UP;
                    break;
            }
            break;
        case DIRECTION_RIGHT:
            switch (snake_body_first.direction) {
                case DIRECTION_UP:
                case DIRECTION_UP_RIGHT:
                case DIRECTION_UP_LEFT:
                    snake_body_first.direction = DIRECTION_RIGHT_UP;
                    break;
                case DIRECTION_DOWN:
                case DIRECTION_DOWN_RIGHT:
                case DIRECTION_DOWN_LEFT:
                    snake_body_first.direction = DIRECTION_RIGHT_DOWN;
                    break;
                case DIRECTION_RIGHT_UP:
                case DIRECTION_RIGHT_DOWN:
                    snake_body_first.direction = DIRECTION_RIGHT;
            }
            break;
        case DIRECTION_DOWN:
            switch (snake_body_first.direction) {
                case DIRECTION_LEFT:
                case DIRECTION_LEFT_UP:
                case DIRECTION_LEFT_DOWN:
                    snake_body_first.direction = DIRECTION_DOWN_LEFT;
                    break;
                case DIRECTION_RIGHT:
                case DIRECTION_RIGHT_UP:
                case DIRECTION_RIGHT_DOWN:
                    snake_body_first.direction = DIRECTION_DOWN_RIGHT;
                    break;
                case DIRECTION_DOWN_LEFT:
                case DIRECTION_DOWN_RIGHT:
                    snake_body_first.direction = DIRECTION_DOWN;
                    break;
            }
            break;
        case DIRECTION_LEFT:
            switch (snake_body_first.direction) {
                case DIRECTION_UP:
                case DIRECTION_UP_RIGHT:
                case DIRECTION_UP_LEFT:
                    snake_body_first.direction = DIRECTION_LEFT_UP;
                    break;
                case DIRECTION_DOWN:
                case DIRECTION_DOWN_RIGHT:
                case DIRECTION_DOWN_LEFT:
                    snake_body_first.direction = DIRECTION_LEFT_DOWN;
                    break;
                case DIRECTION_LEFT_UP:
                case DIRECTION_LEFT_DOWN:
                    snake_body_first.direction = DIRECTION_LEFT;
                    break;
            }
            break;
    }
    game_field[snake_body_first.x + (snake_body_first.y * 20)].direction = snake_body_first.direction;

    // set no snake on old tail position
    index = snake_tail.x + (snake_tail.y * 20);
    game_field[index].has_snake = 0;

    // move the tail to the new direction
    uint8_t tail_direction = game_field[getPreviousTileIndex(&snake_tail)].direction;
    moveSnakeTile(&snake_tail);
    switch (tail_direction) {
        case DIRECTION_UP:
        case DIRECTION_UP_LEFT:
        case DIRECTION_UP_RIGHT:
            snake_tail.direction = DIRECTION_UP;
            break;
        case DIRECTION_RIGHT:
        case DIRECTION_RIGHT_DOWN:
        case DIRECTION_RIGHT_UP:
            snake_tail.direction = DIRECTION_RIGHT;
            break;
        case DIRECTION_DOWN:
        case DIRECTION_DOWN_LEFT:
        case DIRECTION_DOWN_RIGHT:
            snake_tail.direction = DIRECTION_DOWN;
            break;
        case DIRECTION_LEFT:
        case DIRECTION_LEFT_DOWN:
        case DIRECTION_LEFT_UP:
            snake_tail.direction = DIRECTION_LEFT;
            break;
    }
    game_field[snake_tail.x + (snake_tail.y * 20)].direction = snake_tail.direction;

    checkDeath();
    // move the head to the new direction
    snake_head.direction = snake_new_direction;
    moveSnakeTile(&snake_head);

    checkApple();
}

void moveSnakeTile(struct snake_position *tile) {
    switch (tile->direction) {
        case DIRECTION_UP:
        case DIRECTION_UP_RIGHT:
        case DIRECTION_UP_LEFT:
            if (0 == tile->y) {
                tile->y = 17;
            } else {
                tile->y -= 1;
            }
            break;
        case DIRECTION_RIGHT:
        case DIRECTION_RIGHT_UP:
        case DIRECTION_RIGHT_DOWN:
            if (19 == tile->x) {
                tile->x = 0;
            } else {
                tile->x += 1;
            }
            break;
        case DIRECTION_DOWN:
        case DIRECTION_DOWN_RIGHT:
        case DIRECTION_DOWN_LEFT:
            if (17 == tile->y) {
                tile->y = 0;
            } else {
                tile->y += 1;
            }
            break;
        case DIRECTION_LEFT:
        case DIRECTION_LEFT_UP:
        case DIRECTION_LEFT_DOWN:
            if (0 == tile->x) {
                tile->x = 19;
            } else {
                tile->x -= 1;
            }
    }
    uint16_t index = tile->x + (tile->y * 20);
    game_field[index].direction = tile->direction;
    game_field[index].has_snake = 1;
}

void setSnakeDirection(uint8_t direction) {
    snake_new_direction = direction;
}

void snakeUpdate() {
    if (joy_pad_now & J_UP && joy_pad_old != J_UP && DIRECTION_DOWN != snake_head.direction) {
        setSnakeDirection(DIRECTION_UP);
    } else if (joy_pad_now & J_RIGHT && joy_pad_old != J_RIGHT && DIRECTION_LEFT != snake_head.direction) {
        setSnakeDirection(DIRECTION_RIGHT);
    } else if (joy_pad_now & J_DOWN && joy_pad_old != J_DOWN && DIRECTION_UP != snake_head.direction) {
        setSnakeDirection(DIRECTION_DOWN);
    } else if (joy_pad_now & J_LEFT && joy_pad_old != J_LEFT && DIRECTION_RIGHT != snake_head.direction) {
        setSnakeDirection(DIRECTION_LEFT);
    }
    if (0 == snake_alive && joy_pad_now & J_START && joy_pad_old != J_START) {
        initSnake();
        drawSnake();
    }

    snake_frames_left--;
    if (0 == snake_frames_left) {
        snake_frames_left = snake_frames_wait;
        if (snake_alive) {
            moveSnake();
            if (snake_alive) {
                drawSnake();
            }
        }
    }
}
