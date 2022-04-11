#include "piece.h"

Pawn::Pawn(Color col, string str) : Piece::Piece(col, str) {}

bool Pawn::get_castling() const { return 0; }
void Pawn::set_castling() {}

Movement Pawn::is_valid_move(int init_x, int init_y, int dest_x,
                             int dest_y, Piece *chess_tab[8][8]) {

    // check if the move is valid for the chessboard
    if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7)
        return ERROR;
    if (dest_x == init_x && dest_y == init_y)
        return ERROR;

    // test if the move is valid for the pawn

    // black pawn

    if (dest_x - init_x == 1) {
        // moving up one space allowed

        if (chess_tab[dest_x][dest_y] == nullptr)
            return ONE_CASE_BLACK;

    } else if (dest_x - init_x == 2) {
        // movement of two squares up allowed if it is the first
        // movement of the pawn

        if (init_x == 1 && chess_tab[dest_x][dest_y] == nullptr &&
            chess_tab[init_x + 1][dest_y] == nullptr)
            return TWO_CASE_BLACK;

    } else if (dest_x - init_x == 1 && dest_y - init_y == 1) {
        // movement of one square diagonally authorized if there
        // is an opposing pawn

        return DIAGONAL_BLACK;
    } else if (dest_x - init_x == 1 && dest_y - init_y == -1) {
        // movement of one square diagonally authorized if there
        // is an opposing pawn

        return DIAGONAL_BLACK;
    }

    // white pawn

    if (dest_x - init_x == -1) {
        // moving down one space allowed

        if (chess_tab[dest_x][dest_y] == nullptr)
            return ONE_CASE_WHITE;

    } else if (init_x == 6 && dest_x - init_x == -2) {
        // movement of two squares down allowed if it is the first
        // movement of the pawn

        if (chess_tab[dest_x][dest_y] == nullptr &&
            chess_tab[init_x - 1][dest_y] == nullptr)
            return TWO_CASE_WHITE;

    } else if (dest_x - init_x == -1 && dest_y - init_y == 1) {
        // movement of one square diagonally authorized if there
        // is an opposing pawn;

        return DIAGONAL_WHITE;
    } else if (dest_x - init_x == -1 && dest_y - init_y == -1) {
        // movement of one square diagonally authorized if there
        // is an opposing pawn

        return DIAGONAL_WHITE;
    }

    return ERROR;
}