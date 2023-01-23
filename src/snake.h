#include <stdint.h>

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
 * Snake tile position with an x and y coordinate and the direction the tile is moving.
 */
struct snake_position {
    uint8_t x;
    uint8_t y;
    uint8_t direction;
};

/**
 * All the snake tiles on the map.
 * The first tile is the head, the last one the tail.
 */
extern struct snake_position snake[];
/**
 * Holds the last input where the snake goes next. Can only be UP, RIGHT, DOWN or LEFT.
 */
extern uint8_t snake_new_direction;
/**
 * The current snake length.
 */
extern uint16_t snake_size;
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
 * Draws the snake on the screen.
 */
void drawSnake();

/**
 * Draws a snake tile on the screen.
 *
 * @param index
 */
void drawSnakeTile(uint16_t index);

/**
 * Initiates the snake tiles.
 */
void initSnake();

/**
 * Moves the snake one tile.
 */
void moveSnake();

/**
 * Sets the new direction for the snake movement, can only be UP, RIGHT, DOWN or LEFT.
 *
 * @param direction
 */
void setSnakeDirection(uint8_t direction);
