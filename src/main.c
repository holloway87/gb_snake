#include <gb/gb.h>

#include "../res/snake.h"
#include "apple.h"
#include "snake.h"

void clearScreen();

void main() {
    DISPLAY_ON;

    SHOW_BKG;


    set_bkg_data(0, snake_tiles_count, snake_tiles);
    clearScreen();
    initSnake();
    drawSnake();
    setRandomApple();

    const uint8_t frames_wait = 10;
    uint8_t frames_left = frames_wait;

    uint8_t joy_pad_now = 0;
    uint8_t joy_pad_old = 0;

    while (1) {
        joy_pad_old = joy_pad_now;
        joy_pad_now = joypad();

        if (joy_pad_now & J_UP && DIRECTION_DOWN != snake[0].direction) {
            setSnakeDirection(DIRECTION_UP);
        } else if (joy_pad_now & J_RIGHT && DIRECTION_LEFT != snake[0].direction) {
            setSnakeDirection(DIRECTION_RIGHT);
        } else if (joy_pad_now & J_DOWN && DIRECTION_UP != snake[0].direction) {
            setSnakeDirection(DIRECTION_DOWN);
        } else if (joy_pad_now & J_LEFT && DIRECTION_RIGHT != snake[0].direction) {
            setSnakeDirection(DIRECTION_LEFT);
        }

        frames_left--;
        if (0 == frames_left) {
            frames_left = frames_wait;
            moveSnake();
            drawSnake();
        }

        wait_vbl_done();
    }
}

void clearScreen() {
    for (unsigned char y = 0; y < 18; y++) {
        for (unsigned char x = 0; x < 20; x++) {
            set_bkg_tile_xy(x, y, EMPTY_BACKGROUND);
        }
    }
}
