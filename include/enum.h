#ifndef ENUM
#define ENUM

enum Color { EMPTY = 0, WHITE = 1, BLACK = 2 };
enum State { NONE = 0, CHECK = 1, CHECKMATE = 2 };
enum Movement {
    TWO_CASE_WHITE = 0,
    TWO_CASE_BLACK = 1,
    ONE_CASE_WHITE = 2,
    ONE_CASE_BLACK = 3,
    DIAGONAL_WHITE = 4,
    DIAGONAL_BLACK = 5,
    NONE_WHITE = 6,
    NONE_BLACK = 7,
    GOOD = 8,
    ERROR = 9
};

#endif