#include "piece.h"

Pawn::Pawn(Color col, string str)
    : Piece::Piece(col, str), castling(false) {}

bool Pawn::get_castling() const { return castling; }
void Pawn::set_castling() { castling = true; }

void Pawn::promotion(int x, int y, Piece *chess_tab[8][8],
                     Color color) {

    string choice, Q_name, R_name, N_name, B_name;

    if (color == WHITE) {

        Q_name = "\u2655";
        R_name = "\u2656";
        N_name = "\u2658";
        B_name = "\u2657";
    } else {

        Q_name = "\u265B";
        R_name = "\u265C";
        N_name = "\u265E";
        B_name = "\u265D";
    }

    cout << GRN "You can upgrade your pawn. "
         << "Choose between Queen, Rook, Knight or Bishop." << endl;

    cout << "Please enter Q / R / N / B to desginate your choice "
            ": " NC cin >>
        choice;

    bool done = false;
    while (done == false) {

        if (choice == "Q") {

            delete chess_tab[x][y];
            chess_tab[x][y] = new Queen(color, Q_name);
            done = true;
            break;
        } else if (choice == "R") {

            delete chess_tab[x][y];
            chess_tab[x][y] = new Rook(color, R_name);
            done = true;
            break;
        } else if (choice == "N") {

            delete chess_tab[x][y];
            chess_tab[x][y] = new Knight(color, N_name);
            done = true;
            break;
        } else if (choice == "B") {

            delete chess_tab[x][y];
            chess_tab[x][y] = new Bishop(color, B_name);
            done = true;
            break;
        }
    }
}

Movement Pawn::is_valid_move(int init_x, int init_y, int dest_x,
                             int dest_y, Piece *chess_tab[8][8]) {

    // check if the move is valid for the chessboard
    if (dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7)
        return ERROR;
    if (dest_x == init_x && dest_y == init_y)
        return ERROR;

    // test if the move is valid for the pawn

    // black pawn

    if (dest_x - init_x == 1 && dest_y - init_y == 0) {
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

        if (chess_tab[dest_x][dest_y] != nullptr &&
            chess_tab[dest_x][dest_y]->get_color() != get_color())
            return DIAGONAL_BLACK;

    } else if (dest_x - init_x == 1 && dest_y - init_y == -1) {
        // movement of one square diagonally authorized if there
        // is an opposing pawn

        if (chess_tab[dest_x][dest_y] != nullptr &&
            chess_tab[dest_x][dest_y]->get_color() != get_color())
            return DIAGONAL_BLACK;
    }

    // white pawn

    else if (dest_x - init_x == -1 && dest_y - init_y == 0) {
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

        if (chess_tab[dest_x][dest_y] != nullptr &&
            chess_tab[dest_x][dest_y]->get_color() == BLACK)
            return DIAGONAL_WHITE;

    } else if (dest_x - init_x == -1 && dest_y - init_y == -1) {
        // movement of one square diagonally authorized if there
        // is an opposing pawn

        if (chess_tab[dest_x][dest_y] != nullptr &&
            chess_tab[dest_x][dest_y]->get_color() == BLACK)
            return DIAGONAL_WHITE;
    }

    return ERROR;
}