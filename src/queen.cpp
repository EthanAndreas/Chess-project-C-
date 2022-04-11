#include "piece.h"

Queen::Queen(Color col, string str) : Piece::Piece(col, str) {}

bool Queen::get_castling() const { return 0; }
void Queen::set_castling() {}

Movement Queen::is_valid_move(int init_x, int init_y, int dest_x,
                              int dest_y, Piece *chess_tab[8][8]) {

    // check if the move is valid for the chessboard
    if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7)
        return ERROR;
    if (dest_x == init_x && dest_y == init_y)
        return ERROR;

    // test if the move is valid for the queen

    // Two cases :
    int i = init_x, j = init_y;

    // First case : same movement in both axis (Bishop)

    while (chess_tab[i][j] == nullptr && i != dest_x && j != dest_y) {

        i += (dest_x - i > 0) ? 1 : -1;
        j += (dest_y - j > 0) ? 1 : -1;
    }

    if (i != dest_x || j != dest_y)
        return ERROR;

    // Second case : same movement in one axis (Rook)
    if ((dest_x - init_x) != 0 && (dest_y - init_y) != 0)
        return ERROR;

    i = init_x;
    j = init_y;

    if ((dest_x - init_x) != 0) {

        while (chess_tab[i][j] == nullptr && i != dest_x)
            i += (dest_x - i > 0) ? 1 : -1;
    } else {

        while (chess_tab[i][j] == nullptr && j != dest_y)
            j += (dest_y - j > 0) ? 1 : -1;
    }

    if (i != dest_x || j != dest_y)
        return ERROR;

    // one of the two case is respected, so we can move the queen
    return GOOD;
}
