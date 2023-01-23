#include "position.h"

/**
 * Position of the current apple.
 */
extern struct position apple_pos;

/**
 * Draws the apple on the map.
 */
void drawApple();

/**
 * Set a new apple at a random location where the snake is not present.
 */
void setRandomApple();
