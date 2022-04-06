#include "piece.h"

Queen::Queen(Color col, string str) : Piece(col, str) {}

bool Queen::is_valid_move(int init_x, int init_y, int dest_x,
                          int dest_y, Piece ***chess_tab) const {

    // check if the move is valid for the chessboard
    if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7)
        return false;
    if (dest_x == init_x || dest_y == init_y)
        return false;

    // test if the move is valid for the queen

    // Two cases :
    int i = init_x, j = init_y;

    // First case : same movement in both axis (Bishop)

    while (chess_tab[i][j] == nullptr && i != dest_x && j != dest_y) {

        i += (dest_x - i > 0) ? 1 : -1;
        j += (dest_y - j > 0) ? 1 : -1;
    }

    if (i != dest_x || j != dest_y)
        return false;

    if (chess_tab[i][j] != nullptr) {

        // we eat the piece of the opponent
        if (chess_tab[i][j]->get_color() !=
            chess_tab[init_x][init_y]->get_color())
            return true;

        return false;
    }

    // Second case : same movement in one axis (Rook)
    if ((dest_x - init_x) != 0 && (dest_y - init_y) != 0)
        return false;

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
        return false;

    if (chess_tab[i][j] != nullptr) {

        // we eat the piece of the opponent
        if (chess_tab[i][j]->get_color() !=
            chess_tab[init_x][init_y]->get_color())
            return true;

        return false;
    }

    // one of the two case is respected, so we can move the queen
    return true;
}
