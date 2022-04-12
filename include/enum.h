#ifndef ENUM
#define ENUM

// reset
#define NC "\e[0m"
// text color
#define BLU "\e[30m"
#define RED "\e[31m"
#define GRN "\e[32m"
#define YEL "\e[33m"
#define CYN1 "\e[34m"
#define MAG "\e[35m"
#define CYN2 "\e[36m"
#define WHT "\e[37m"
// background color
#define BLU_B "\e[40m"
#define RED_B "\e[41m"
#define GRN_B "\e[42m"
#define ORA_B "\e[43m"
#define CYN1_B "\e[44m"
#define YEL_B "\e[45m"
#define CYN2_B "\e[46m"
#define WHT_B "\e[47m"

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