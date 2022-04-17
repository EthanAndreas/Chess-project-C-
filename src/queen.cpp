#include "piece.h"

Queen::Queen(Color col, string str)
    : Piece::Piece(col, str), castling(false) {}

bool Queen::get_castling() const { return castling; }
void Queen::set_castling() { castling = true; }

bool Queen::is_valid_move(int init_x, int init_y, int dest_x,
                          int dest_y, Piece *chess_tab[8][8]) {

    // check if the move is valid for the chessboard
    if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7)
        return false;
    if (dest_x == init_x && dest_y == init_y)
        return false;

    // test if the move is valid for the queen

    // Two cases :
    int i = init_x, j = init_y;

    // First case : same movement in both axis (Bishop)

    // first move
    if (dest_x - init_x > 0)
        i = init_x + 1;
    else
        i = init_x - 1;

    if (dest_y - init_y > 0)
        j = init_y + 1;
    else
        j = init_y - 1;

    while (chess_tab[i][j] == nullptr && i != dest_x && j != dest_y) {

        i += (dest_x - i > 0) ? 1 : -1;
        j += (dest_y - j > 0) ? 1 : -1;
    }

    if (i == dest_x && j == dest_y)
        return true;

    // Second case : same movement in one axis (Rook)
    if ((dest_x - init_x) != 0 && (dest_y - init_y) != 0)
        return false;

    int i = init_x, j = init_y;

    if ((dest_x - init_x) != 0) {

        // first move
        i += (dest_x - init_x > 0) ? 1 : -1;
        // move's rest
        while (chess_tab[i][j] == nullptr && i != dest_x)
            i += (dest_x - i > 0) ? 1 : -1;
    } else {

        // first move
        j += (dest_y - init_y > 0) ? 1 : -1;
        // move's rest
        while (chess_tab[i][j] == nullptr && j != dest_y)
            j += (dest_y - j > 0) ? 1 : -1;
    }

    if (i != dest_x || j != dest_y)
        return false;

    return true;
}
