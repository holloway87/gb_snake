#include <gb/gb.h>

#include "../res/snake.h"
#include "game.h"
#include "snake.h"
#include "start_screen.h"

void startScreenUpdate() {
    if (joy_pad_now & J_START) {
        set_bkg_data(0, snake_tiles_count, snake_tiles);
        clearScreen();
        initSnake();
        game_state = STATE_GAME;
    }
}
