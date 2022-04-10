#include "piece.h"

King::King(Color col, string str) : Piece::Piece(col, str) {}

bool King::get_castling() const { return castling; }

void King::set_castling() { castling = true; }

Movement King::is_valid_move(int init_x, int init_y, int dest_x,
                             int dest_y,
                             Piece *chess_tab[8][8]) const {

    // check if the move is valid for the chessboard
    if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7)
        return ERROR;
    if (dest_x == init_x || dest_y == init_y)
        return ERROR;

    // test if the move is valid for the King
    if (dest_y - init_y == 1) {
        // moving up one space allowed

        return GOOD;
    } else if (dest_y - init_y == 1 && dest_x - init_x == 1) {
        // movement of one square diagonally authorized

        return GOOD;
    } else if (dest_y - init_y == 1 && dest_x - init_x == -1) {
        // movement of one square diagonally authorized

        return GOOD;
    } else if (dest_y - init_y == -1) {
        // moving down one space allowed

        return GOOD;
    } else if (dest_y - init_y == -1 && dest_x - init_x == 1) {
        // movement of one square diagonally authorized

        return GOOD;
    } else if (dest_y - init_y == -1 && dest_x - init_x == -1) {
        // movement of one square diagonally authorized

        return GOOD;
    } else
        return ERROR;
}
