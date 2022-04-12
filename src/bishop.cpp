#include "piece.h"

Bishop::Bishop(Color col, string str)
    : Piece::Piece(col, str), castling(false) {}

bool Bishop::get_castling() const { return castling; }
void Bishop::set_castling() { castling = true; }

Movement Bishop::is_valid_move(int init_x, int init_y, int dest_x,
                               int dest_y, Piece *chess_tab[8][8]) {

    // check if the move is valid for the chessboard
    if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7)
        return ERROR;
    if (dest_x == init_x && dest_y == init_y)
        return ERROR;

    // test if the move is valid for the bishop
    int i = init_x, j = init_y;

    // first move
    if (dest_x - init_x > 0)
        i = init_x + 1;
    else
        i = init_x - 1;

    if (dest_y - init_y > 0)
        j = init_y + 1;
    else
        j = init_y - 1;

    // move's rest
    while (chess_tab[i][j] == nullptr && i != dest_x && j != dest_y) {

        i += (dest_x - i > 0) ? 1 : -1;
        j += (dest_y - j > 0) ? 1 : -1;
    }

    if (i != dest_x || j != dest_y)
        return ERROR;

    return GOOD;
}