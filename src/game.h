#ifndef GAME_H
#define GAME_H

#include <stdint.h>

enum GAME_STATE {
    STATE_START_SCREEN = 0,
    STATE_GAME = 1
};

/**
 * Determines the game state.
 */
extern uint8_t game_state;

/**
 * The current joy pad value.
 */
extern uint8_t joy_pad_now;

/**
 * The last joy pad value.
 */
extern uint8_t joy_pad_old;

/**
 * Clears the entire screen.
 */
void clearScreen();

#endif
