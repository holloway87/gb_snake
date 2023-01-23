#include "position.h"

/**
 * Position of the current apple.
 */
extern struct position apple_pos;

extern struct position position_list[];
extern uint16_t position_list_max;

/**
 * Draws the apple on the map.
 */
void drawApple();

/**
 * Set a new apple at a random location where the snake is not present.
 */
void setRandomApple();
