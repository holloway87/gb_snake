#include <stdint.h>

#define snake_tiles_count 16
#define EMPTY_BACKGROUND 0
#define SNAKE_HEAD_UP 1
#define SNAKE_HEAD_RIGHT 2
#define SNAKE_HEAD_DOWN 3
#define SNAKE_HEAD_LEFT 4
#define SNAKE_TAIL_DOWN 5
#define SNAKE_TAIL_LEFT 6
#define SNAKE_TAIL_UP 7
#define SNAKE_TAIL_RIGHT 8
#define SNAKE_BODY_UP 9
#define SNAKE_BODY_RIGHT 10
#define SNAKE_BODY_DOWN_RIGHT 11
#define SNAKE_BODY_LEFT_DOWN 12
#define SNAKE_BODY_LEFT_UP 13
#define SNAKE_BODY_UP_RIGHT 14
#define APPLE 15

extern const uint8_t snake_tiles[];
