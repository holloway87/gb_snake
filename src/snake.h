#include <stdint.h>

#include "position.h"

enum DIRECTION_CONSTANTS {
    DIRECTION_UP = 0,
    DIRECTION_RIGHT = 1,
    DIRECTION_DOWN = 2,
    DIRECTION_LEFT = 3,
    /**
     * New direction right, old direction up
     */
    DIRECTION_RIGHT_UP = 4,
    /**
     * New direction down, old direction left
     */
    DIRECTION_DOWN_LEFT = 5,
    /**
     * New direction down, old direction right
     */
    DIRECTION_DOWN_RIGHT = 6,
    /**
     * New direction left, old direction up
     */
    DIRECTION_LEFT_UP = 7,
    /**
     * New direction up, old direction right
     */
    DIRECTION_UP_RIGHT = 8,
    /**
     * New direction left, old direction down
     */
    DIRECTION_LEFT_DOWN = 9,
    /**
     * New direction up, old direction left
     */
    DIRECTION_UP_LEFT = 10,
    /**
     * New direction right, old direction down
     */
    DIRECTION_RIGHT_DOWN = 11
};

/**
 * Holds information about every game field.
 */
struct game_field_info {
    uint8_t x;
    uint8_t y;
    uint8_t direction;
    uint8_t has_snake;
};

/**
 * Game field info.
 */
extern struct game_field_info game_field[];

/**
 * Advancing pointer for the game field info.
 */
extern struct game_field_info *game_field_ptr;

/**
 * Snake tile position with an x and y coordinate and the direction the tile is moving.
 */
struct snake_position {
    uint8_t x;
    uint8_t y;
    uint8_t direction;
};

/**
 * Whether the snake is still alive.
 */
extern uint8_t snake_alive;

/**
 * The first body part of the snake after the head.
 */
extern struct snake_position snake_body_first;

/**
 * How many frame we wait until the snake moves again.
 */
extern uint8_t snake_frames_wait;

/**
 * How many frame are left until we move the snake again.
 */
extern uint8_t snake_frames_left;

/**
 * The heads position and direction.
 */
extern struct snake_position snake_head;

/**
 * Flag if we need to draw the whole snake for the first time.
 */
extern uint8_t snake_initial_draw;

/**
 * The tail position of the last tick, to remove the tile on the background.
 */
extern struct position snake_last_position;

/**
 * Holds the last input where the snake goes next. Can only be UP, RIGHT, DOWN or LEFT.
 */
extern uint8_t snake_new_direction;

/**
 * The current snake length.
 */
extern uint16_t snake_size;

/**
 * The tails position and direction.
 */
extern struct snake_position snake_tail;

/**
 * The amount of snake tiles to add to the end.
 */
extern uint8_t snake_tiles_add;

/**
 * Adds a snake tile at the end.
 */
void addSnake();

/**
 * Checks if the snake head is on the apple.
 */
void checkApple();

/**
 * Checks if the head bumped into something.
 */
void checkDeath();

/**
 * Draws the snake on the screen.
 */
void drawSnake();

/**
 * Draws a snake tile on the screen.
 *
 * @param game_field_index
 */
void drawSnakeTile(struct game_field_info *game_field_index);

/**
 * Returns the index from the previous tile.
 *
 * @param tile the current tile
 * @return the index from the previous tile
 */
uint16_t getPreviousTileIndex(struct snake_position *tile);

/**
 * Initiates the snake tiles.
 */
void initSnake();

/**
 * Moves the snake one tile.
 */
void moveSnake();

/**
 * Moves one snake tile.
 */
void moveSnakeTile(struct snake_position *tile);

/**
 * Sets the new direction for the snake movement, can only be UP, RIGHT, DOWN or LEFT.
 *
 * @param direction
 */
void setSnakeDirection(uint8_t direction);

/**
 * Update the logic in the game state.
 */
void snakeUpdate();
