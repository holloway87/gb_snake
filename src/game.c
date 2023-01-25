#include <gb/gb.h>

#include "../res/snake.h"
#include "game.h"

uint8_t game_state = STATE_START_SCREEN;
uint8_t joy_pad_now = 0;
uint8_t joy_pad_old = 0;

void clearScreen() {
    for (unsigned char y = 0; y < 18; y++) {
        for (unsigned char x = 0; x < 20; x++) {
            set_bkg_tile_xy(x, y, EMPTY_BACKGROUND);
        }
    }
}
