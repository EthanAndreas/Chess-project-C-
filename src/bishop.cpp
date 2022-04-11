#include "piece.h"

Bishop::Bishop(Color col, string str) : Piece::Piece(col, str) {}

bool Bishop::get_castling() const { return 0; }
void Bishop::set_castling() {}

Movement Bishop::is_valid_move(int init_x, int init_y, int dest_x,
                               int dest_y, Piece *chess_tab[8][8]) {

    // check if the move is valid for the chessboard
    if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7)
        return ERROR;
    if (dest_x == init_x && dest_y == init_y)
        return ERROR;

    // test if the move is valid for the bishop
    int i = init_x, j = init_y;

    while (chess_tab[i][j] == nullptr && i != dest_x && j != dest_y) {

        i += (dest_x - i > 0) ? 1 : -1;
        j += (dest_y - j > 0) ? 1 : -1;
    }

    if (i != dest_x || j != dest_y)
        return ERROR;

    return GOOD;
}