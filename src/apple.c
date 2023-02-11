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
    position_list_max = 0;
    game_field_ptr = game_field;
    uint16_t counter = 0;
    do {
        if (0 == game_field_ptr->has_snake) {
            position_list[position_list_max].x = game_field_ptr->x;
            position_list[position_list_max].y = game_field_ptr->y;
            position_list_max++;
        }

        game_field_ptr++;
        counter++;
    } while (360 > counter);

    uint16_t index = randw() % position_list_max;

    apple_pos.x = position_list[index].x;
    apple_pos.y = position_list[index].y;
    drawApple();
}
