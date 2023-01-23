#include <stdint.h>

#define snake_tiles_count 16
#define SNAKE_HEAD_UP 0
#define SNAKE_HEAD_RIGHT 1
#define SNAKE_HEAD_DOWN 2
#define SNAKE_HEAD_LEFT 3
#define SNAKE_TAIL_DOWN 4
#define SNAKE_TAIL_LEFT 5
#define SNAKE_TAIL_UP 6
#define SNAKE_TAIL_RIGHT 7
#define SNAKE_BODY_UP 8
#define SNAKE_BODY_RIGHT 9
#define SNAKE_BODY_DOWN_RIGHT 10
#define SNAKE_BODY_LEFT_DOWN 11
#define SNAKE_BODY_LEFT_UP 12
#define SNAKE_BODY_UP_RIGHT 13
#define APPLE 14
#define EMPTY_BACKGROUND 15

extern const uint8_t snake_tiles[];
