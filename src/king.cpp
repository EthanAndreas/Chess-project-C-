#include "piece.h"

King::King(Color col, string str) : Piece::Piece(col, str) {}

bool King::is_valid_move(int init_x, int init_y, int dest_x,
                         int dest_y, Piece *chess_tab[8][8]) const {

    // check if the move is valid for the chessboard
    if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7)
        return false;
    if (dest_x == init_x || dest_y == init_y)
        return false;

    // test if the move is valid for the King
    // move only if the king is not put in check
    if (dest_y - init_y == 1) {
        // moving up one space allowed

        if (chess_tab[dest_x][dest_y] == nullptr)
            return true;

        if (chess_tab[dest_x][dest_y] != nullptr &&
            chess_tab[dest_x][dest_y]->get_color() !=
                chess_tab[init_x][init_y]->get_color())
            return true;

        return false;

    } else if (dest_y - init_y == 1 && dest_x - init_x == 1) {
        // movement of one square diagonally authorized if there
        // is an opposing pawn

        if (chess_tab[dest_x][dest_y] == nullptr)
            return true;

        if (chess_tab[dest_x][dest_y] != nullptr &&
            chess_tab[dest_x][dest_y]->get_color() !=
                chess_tab[init_x][init_y]->get_color())
            return true;

        return false;
    } else if (dest_y - init_y == 1 && dest_x - init_x == -1) {
        // movement of one square diagonally authorized if there
        // is an opposing pawn

        if (chess_tab[dest_x][dest_y] == nullptr)
            return true;

        if (chess_tab[dest_x][dest_y] != nullptr &&
            chess_tab[dest_x][dest_y]->get_color() !=
                chess_tab[init_x][init_y]->get_color())
            return true;

        return false;

    } else if (dest_y - init_y == -1) {
        // moving down one space allowed

        if (chess_tab[dest_x][dest_y] == nullptr)
            return true;

        if (chess_tab[dest_x][dest_y] != nullptr &&
            chess_tab[dest_x][dest_y]->get_color() !=
                chess_tab[init_x][init_y]->get_color())
            return true;

        return false;
    } else if (dest_y - init_y == -1 && dest_x - init_x == 1) {
        // movement of one square diagonally authorized if there
        // is an opposing pawn

        if (chess_tab[dest_x][dest_y] == nullptr)
            return true;

        if (chess_tab[dest_x][dest_y] != nullptr &&
            chess_tab[dest_x][dest_y]->get_color() !=
                chess_tab[init_x][init_y]->get_color())
            return true;

        return false;
    } else if (dest_y - init_y == -1 && dest_x - init_x == -1) {
        // movement of one square diagonally authorized if there
        // is an opposing pawn

        if (chess_tab[dest_x][dest_y] == nullptr)
            return true;

        if (chess_tab[dest_x][dest_y] != nullptr &&
            chess_tab[dest_x][dest_y]->get_color() !=
                chess_tab[init_x][init_y]->get_color())
            return true;

        return false;
    } else
        return false;

    // case of king in check
}
