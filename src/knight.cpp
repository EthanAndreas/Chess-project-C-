#include "piece.h"

Knight::Knight(Color col, string str) : Piece(col, str) {}

bool Knight::get_castling() const { return 0; }
void Knight::set_castling() {}

Movement Knight::is_valid_move(int init_x, int init_y, int dest_x,
                               int dest_y, Piece *chess_tab[8][8]) {

    cout << "in knight" << endl;

    // check if the move is valid for the chessboard
    if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7)
        return ERROR;
    if (dest_x == init_x && dest_y == init_y)
        return ERROR;

    // test if the move is valid for the knight
    if (dest_x - init_x == 2 && dest_y - init_y == 1)
        return GOOD;
    else if (dest_x - init_x == 1 && dest_y - init_y == 2)
        return GOOD;
    else if (dest_x - init_x == 2 && dest_y - init_y == -1)
        return GOOD;
    else if (dest_x - init_x == -1 && dest_y - init_y == 2)
        return GOOD;
    else if (dest_x - init_x == -2 && dest_y - init_y == 1)
        return GOOD;
    else if (dest_x - init_x == -1 && dest_y - init_y == -2)
        return GOOD;
    else if (dest_x - init_x == -2 && dest_y - init_y == -1)
        return GOOD;
    else if (dest_x - init_x == 1 && dest_y - init_y == -2)
        return GOOD;
    else
        return ERROR;
}
