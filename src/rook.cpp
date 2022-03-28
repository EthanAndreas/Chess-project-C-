#include "piece.h"

Rook::Rook(Color col, string str) : Piece(col, str) {}

bool Rook::is_valid_move(int init_x, int init_y, int dest_x,
                         int dest_y, Piece ***chess_tab) const {

    if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7)
        return false;

    if (dest_x == init_x || dest_y == init_y)
        return false;

    if ((dest_x - init_x) != 0 && (dest_y - init_y) != 0)
        return false;

    int i = init_x, j = init_y;

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

        if (chess_tab[i][j]->get_color() !=
            chess_tab[init_x][init_y]->get_color())
            return true;

        return false;
    }

    return true;
}