#include <gb/gb.h>

#include "../res/snake.h"
#include "apple.h"

struct position apple_pos;

void drawApple() {
    set_bkg_tile_xy(apple_pos.x, apple_pos.y, APPLE);
}

void setRandomApple() {
    apple_pos.x = 1;
    apple_pos.y = 1;
    drawApple();
}
