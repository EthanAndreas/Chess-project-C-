#include "chessboard.h"
#include "piece.h"
using namespace std;

Chessboard::Chessboard() {

    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++)
            chess_tab[i][j] = nullptr;
    }

    // Initialisation of pieces
    chess_tab[0][0] = new Rook(Color::White, "\u2656");
    // chess_tab[0][1] = new Knight(Color::White, "\u2658");
    chess_tab[0][2] = new Bishop(Color::White, "\u2657");
    // chess_tab[0][3] = new Queen(Color::White, "\u2655");
    // chess_tab[0][4] = new King(Color::White, "\u2654");
    chess_tab[0][5] = new Bishop(Color::White, "\u2657");
    // chess_tab[0][6] = new Knight(Color::White, "\u2658");
    chess_tab[0][7] = new Rook(Color::White, "\u2656");
    chess_tab[7][0] = new Rook(Color::Black, "\u265C");
    // chess_tab[7][1] = new Knight(Color::Black, "\u265E");
    chess_tab[7][2] = new Bishop(Color::Black, "\u265D");
    // chess_tab[7][3] = new Queen(Color::Black, "\u265B");
    // chess_tab[7][4] = new King(Color::Black, "\u265A");
    chess_tab[7][5] = new Bishop(Color::Black, "\u265D");
    // chess_tab[7][6] = new Knight(Color::Black, "\u265E");
    chess_tab[7][7] = new Rook(Color::Black, "\u265C");

    for (int i = 0; i < 8; i++) {
        // chess_tab[1][i] = new Pawn(Color::White, "\u2659");
        // chess_tab[6][i] = new Pawn(Color::Black, "\u265F");
    }
}

Chessboard::~Chessboard() {

    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++) {

            if (chess_tab[i][j])
                delete chess_tab[i][j];
        }
    }
}

void Chessboard::print_board() {

    static const string &space = "     ";
    static const string &line =
        "  +-----+-----+-----+-----+-----+-----+-----+-----+";

    // print the column name
    cout << "     a     b     c     d     e     f     g     h    "
         << endl;
    cout << line << endl;

    for (int i = 7; i >= 0; i--) {

        // print the line number
        cout << i + 1 << " ";

        for (int j = 0; j < 8; j++) {

            // separator between column
            cout << "|";

            if (chess_tab[i][j] != nullptr) {

                // chess_tab[i][j]->print();
                cout << space;

            } else
                cout << space;
        }

        cout << "|";
        cout << endl << line << endl;
    }
}