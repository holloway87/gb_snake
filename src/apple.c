#include <gb/gb.h>
#include <rand.h>

#include "../res/snake.h"
#include "apple.h"
#include "snake.h"

struct position apple_pos;
struct position position_list[360];
uint16_t position_list_max;

void drawApple() {
    set_bkg_tile_xy(apple_pos.x, apple_pos.y, APPLE);
}

void setRandomApple() {
    // this is VERY inefficient
    position_list_max = 0;
    for (uint8_t y = 0; y < 18; y++) {
        for (uint8_t x = 0; x < 20; x++) {
            uint8_t found = 0;
            for (uint16_t i = 0; i < snake_size; i++) {
                if (x == snake[i].x && y == snake[i].y) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                position_list[position_list_max].x = x;
                position_list[position_list_max].y = y;
                position_list_max++;
            }
        }
    }

    uint16_t index = randw() % (position_list_max +1);

    apple_pos.x = position_list[index].x;
    apple_pos.y = position_list[index].y;
    drawApple();
}
