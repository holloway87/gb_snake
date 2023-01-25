#include <gb/gb.h>

#include "../res/start_screen.h"
#include "../res/snake.h"
#include "apple.h"
#include "game.h"
#include "snake.h"
#include "start_screen.h"


void main() {
    DISPLAY_ON;

    SHOW_BKG;

    set_bkg_data(0, start_screen_tiles_count, start_screen_tiles);
    set_bkg_tiles(0, 0, start_screen_tiles_width, start_screen_tiles_height, start_screen_map);

    while (1) {
        joy_pad_old = joy_pad_now;
        joy_pad_now = joypad();

        switch (game_state) {
            case STATE_START_SCREEN:
                startScreenUpdate();
                break;
            case STATE_GAME:
                snakeUpdate();
                break;
        }

        wait_vbl_done();
    }
}
