#include "piece.h"

Pawn::Pawn(Color col, string str) : Piece::Piece(col, str) {}

bool Pawn::is_valid_move(int init_x, int init_y, int dest_x,
                         int dest_y, Piece *chess_tab[8][8]) const {

    // check if the move is valid for the chessboard
    if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7)
        return false;
    if (dest_x == init_x || dest_y == init_y)
        return false;

    // test if the move is valid for the pawn
    if (chess_tab[init_x][init_y]->get_color() == WHITE) {
        // white pawn

        if (dest_y - init_y == 1) {
            // moving up one space allowed

            if (chess_tab[dest_x][dest_y] == nullptr)
                return true;

            return false;
        } else if (dest_y - init_y == 2) {
            // movement of two squares up allowed if it is the first
            // movement of the pawn

            if (init_y == 1 && chess_tab[dest_x][dest_y] == nullptr &&
                chess_tab[dest_x][init_y + 1] == nullptr)
                return true;

            return false;
        } else if (dest_y - init_y == 1 && dest_x - init_x == 1) {
            // movement of one square diagonally authorized if there
            // is an opposing pawn

            if (chess_tab[dest_x][dest_y] != nullptr &&
                chess_tab[dest_x][dest_y]->get_color() !=
                    chess_tab[init_x][init_y]->get_color())
                return true;

            return false;
        } else if (dest_y - init_y == 1 && dest_x - init_x == -1) {
            // movement of one square diagonally authorized if there
            // is an opposing pawn

            if (chess_tab[dest_x][dest_y] != nullptr &&
                chess_tab[dest_x][dest_y]->get_color() !=
                    chess_tab[init_x][init_y]->get_color())
                return true;

            return false;
        } else
            return false;
    } else {
        // black pawn

        if (dest_y - init_y == -1) {
            // moving down one space allowed

            if (chess_tab[dest_x][dest_y] == nullptr)
                return true;

            return false;
        } else if (init_y == 6 && dest_y - init_y == -2) {
            // movement of two squares down allowed if it is the first
            // movement of the pawn

            if (chess_tab[dest_x][dest_y] == nullptr &&
                chess_tab[dest_x][init_y - 1] == nullptr)
                return true;

            return false;
        } else if (dest_y - init_y == -1 && dest_x - init_x == 1) {
            // movement of one square diagonally authorized if there
            // is an opposing pawn

            if (chess_tab[dest_x][dest_y] != nullptr &&
                chess_tab[dest_x][dest_y]->get_color() !=
                    chess_tab[init_x][init_y]->get_color())
                return true;

            return false;
        } else if (dest_y - init_y == -1 && dest_x - init_x == -1) {
            // movement of one square diagonally authorized if there
            // is an opposing pawn

            if (chess_tab[dest_x][dest_y] != nullptr &&
                chess_tab[dest_x][dest_y]->get_color() !=
                    chess_tab[init_x][init_y]->get_color())
                return true;

            return false;
        } else
            return false;
    }

    return false;
}