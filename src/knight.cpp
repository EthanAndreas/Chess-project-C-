#include "piece.h"

Knight::Knight(Color col, string str) : Piece(col, str) {}

bool Knight::is_valid_move(int init_x, int init_y, int dest_x,
                           int dest_y, Piece *chess_tab[8][8]) const {

    // check if the move is valid for the chessboard
    if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7)
        return false;
    if (dest_x == init_x || dest_y == init_y)
        return false;

    int valid = 0;

    // test if the move is valid for the knight
    if (dest_x - init_x == 2 && dest_y - init_y == 1)
        valid = 1;
    else if (dest_x - init_x == 1 && dest_y - init_y == 2)
        valid = 1;
    else if (dest_x - init_x == 2 && dest_y - init_y == -1)
        valid = 1;
    else if (dest_x - init_x == -1 && dest_y - init_y == 2)
        valid = 1;
    else if (dest_x - init_x == -2 && dest_y - init_y == 1)
        valid = 1;
    else if (dest_x - init_x == -1 && dest_y - init_y == -2)
        valid = 1;
    else if (dest_x - init_x == -2 && dest_y - init_y == -1)
        valid = 1;
    else if (dest_x - init_x == 1 && dest_y - init_y == -2)
        valid = 1;
    else
        valid = 0;

    if (valid == 1) {
        if (chess_tab[dest_x][dest_y] != nullptr) {
            // we eat the piece of the opponent
            if (chess_tab[dest_x][dest_y]->get_color() !=
                chess_tab[init_x][init_y]->get_color())
                return true;
            return false;
        }
        return true;
    } else
        return false;
}
