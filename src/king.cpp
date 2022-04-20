#include "piece.h"

King::King(Color col, string str)
    : Piece::Piece(col, str), castling(false) {}

bool King::get_castling() const { return castling; }

void King::set_castling() { castling = true; }

bool King::is_valid_move(int init_x, int init_y, int dest_x,
                         int dest_y, Piece *chess_tab[8][8]) {

    (void)chess_tab;

    // check if the move is valid for the chessboard
    if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7)
        return false;
    if (dest_x == init_x && dest_y == init_y)
        return false;

    // test if the move is valid for the King
    if (abs(dest_x - init_x) <= 1 && abs(dest_y - init_y) <= 1) {
        // move is valid

        return true;
    }

    return false;
}
