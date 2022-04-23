#include "piece.h"

Queen::Queen(Color col, string str)
    : Piece::Piece(col, str), castling(false) {}

bool Queen::get_castling() const { return castling; }
void Queen::set_castling() { castling = true; }

bool Queen::is_valid_move(int init_x, int init_y, int dest_x,
                          int dest_y, Piece *chess_tab[8][8]) {

    // one-axis move

    // horizontal move
    if (init_y == dest_y) {

        if (init_x < dest_x) {

            for (int i(init_x + 1); i < dest_x; i++) {

                if (chess_tab[i][init_y] != nullptr)
                    return false;
            }
        } else {

            for (int i = dest_x + 1; i < init_x; i++) {

                if (chess_tab[i][init_y] != nullptr)
                    return false;
            }
        }

        return true;
    }

    // vertical move
    if (init_x == dest_x) {

        if (init_y < dest_y) {

            for (int i = init_y + 1; i < dest_y; i++) {

                if (chess_tab[init_x][i] != nullptr)
                    return false;
            }
        } else {
            for (int i = dest_y + 1; i < init_y; i++) {

                if (chess_tab[init_x][i] != nullptr)
                    return false;
            }
        }

        return true;
    }

    // diagonal move
    if (abs(init_x - dest_x) != abs(init_y - dest_y))
        return false;

    // upper-right diagonal
    if (init_x < dest_x && init_y < dest_y) {

        for (int i = 1; i < (dest_x - init_x); i++) {

            if (chess_tab[init_x + i][init_y + i] != nullptr)
                return false;
        }
    }
    // lower-right diagonal
    else if (init_x < dest_x && dest_y < init_y) {

        for (int i = 1; i < (dest_x - init_x); i++) {

            if (chess_tab[init_x + i][init_y - i] != nullptr)
                return false;
        }
    }
    // upper-left diagonal
    else if (dest_x < init_x && init_y < dest_y) {

        for (int i = 1; i < (init_x - dest_x); i++) {

            if (chess_tab[init_x - i][init_y + i] != nullptr)
                return false;
        }
    }
    // lower-left diagonal
    else if (dest_x < init_x && dest_y < init_y) {

        for (int i = 1; i < (init_x - dest_x); i++) {

            if (chess_tab[init_x - i][init_y - i] != nullptr)
                return false;
        }
    } else
        return false;

    return true;
}
