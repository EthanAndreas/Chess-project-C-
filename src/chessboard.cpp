#include "chessboard.h"
#include "piece.h"
using namespace std;

Chessboard::Chessboard() {

    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++)
            chess_tab[i][j] = nullptr;
    }

    // Initialisation of pieces
    chess_tab[0][0] = new Rook(Color::BLACK, "\u2656");
    chess_tab[0][1] = new Knight(Color::BLACK, "\u2658");
    chess_tab[0][2] = new Bishop(Color::BLACK, "\u2657");
    chess_tab[0][3] = new Queen(Color::BLACK, "\u2655");
    chess_tab[0][4] = new King(Color::BLACK, "\u2654");
    chess_tab[0][5] = new Bishop(Color::BLACK, "\u2657");
    chess_tab[0][6] = new Knight(Color::BLACK, "\u2658");
    chess_tab[0][7] = new Rook(Color::BLACK, "\u2656");
    chess_tab[7][0] = new Rook(Color::WHITE, "\u265C");
    chess_tab[7][1] = new Knight(Color::WHITE, "\u265E");
    chess_tab[7][2] = new Bishop(Color::WHITE, "\u265D");
    chess_tab[7][3] = new Queen(Color::WHITE, "\u265B");
    chess_tab[7][4] = new King(Color::WHITE, "\u265A");
    chess_tab[7][5] = new Bishop(Color::WHITE, "\u265D");
    chess_tab[7][6] = new Knight(Color::WHITE, "\u265E");
    chess_tab[7][7] = new Rook(Color::WHITE, "\u265C");

    for (int i = 0; i < 8; i++) {
        chess_tab[1][i] = new Pawn(Color::BLACK, "\u2659");
        chess_tab[6][i] = new Pawn(Color::WHITE, "\u265F");
    }

    chess_tab[5][1] = new Pawn(Color::BLACK, "\u2659");
    // save of king's location
    white_king_x = 7;
    white_king_y = 4;
    black_king_x = 0;
    black_king_y = 4;
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

    static const string &space = "    ";
    static const string &space1 = " ";
    static const string &space2 = "  ";

    int order;

    // print the column name
    cout << endl
         << RED "   a" WHT "   b" RED "   c" WHT "   d" RED "   e" WHT
                "   f" RED "   g" WHT "   h" NC
         << endl;

    for (int i = 7; i >= 0; i--) {

        if (i % 2 == 0) {
            // print the line number
            cout << WHT;
            cout << i + 1 << " ";
            cout << NC;
            order = 0;
        } else {
            // print the line number
            cout << RED;
            cout << i + 1 << " ";
            cout << NC;
            order = 1;
        }

        for (int j = 0; j < 8; j++) {

            // // separator between column
            // cout << "|";

            if (chess_tab[i][j] != nullptr) {

                if (j % 2 == order) {
                    cout << BLU_B;
                    cout << space1;
                    chess_tab[i][j]->print();
                    cout << space2;
                    cout << NC;
                } else {
                    cout << RED_B;
                    cout << space1;
                    chess_tab[i][j]->print();
                    cout << space2;
                    cout << NC;
                }

            } else {
                if (j % 2 == order) {
                    cout << BLU_B;
                    cout << space;
                    cout << NC;
                } else {
                    cout << RED_B;
                    cout << space;
                    cout << NC;
                }
            }
        }

        // // cout << "|";
        // cout << endl << line << endl;
        cout << endl;
    }
}

Piece *Chessboard::get_piece(int x, int y) const {

    if (x < 0 || x > 7 || y < 0 || y > 7)
        return nullptr;

    return chess_tab[x][y];
}

void Chessboard::move(int init_x, int init_y, int dest_x,
                      int dest_y) {

    // security
    if (chess_tab[init_x][init_y] == nullptr)
        return;

    // in the case where the player destrinit_y an opponent piece
    if (chess_tab[dest_x][dest_y] != nullptr)
        delete chess_tab[dest_x][dest_y];

    // save that the piece has move at least once
    chess_tab[init_x][init_y]->set_castling();

    // move the piece
    chess_tab[dest_x][dest_y] = chess_tab[init_x][init_y];
    chess_tab[init_x][init_y] = nullptr;
}

bool Chessboard::is_check(Color color) {
    // test if color's pawns are in check

    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++) {

            if (chess_tab[i][j] != nullptr &&
                chess_tab[i][j]->get_color() != color) {

                if (color == BLACK) {

                    // the piece is a white pawn, the only move to
                    // put king in check is a diagonal move
                    if (get_piece(i, j)->get_name() == "\u265F") {

                        if (chess_tab[i][j]->is_valid_move(
                                i, j, black_king_x, black_king_y,
                                chess_tab) == DIAGONAL_WHITE)
                            return true;
                    }

                    // we try if all other pieces can touch the
                    // king
                    if (get_piece(i, j)->is_valid_move(
                            i, j, black_king_x, black_king_y,
                            chess_tab) == GOOD)
                        return true;
                } else {

                    // the piece is a white pawn, the only move to
                    // put king in check is a diagonal move
                    if (get_piece(i, j)->get_name() == "\u2659") {

                        if (chess_tab[i][j]->is_valid_move(
                                i, j, white_king_x, white_king_y,
                                chess_tab) == DIAGONAL_BLACK)
                            return true;
                    }

                    // we try if all other pieces can touch the
                    // king
                    if (get_piece(i, j)->is_valid_move(
                            i, j, white_king_x, white_king_y,
                            chess_tab) == GOOD)
                        return true;
                }
            }
        }
    }

    return false;
}

bool Chessboard::is_checkmate(Color color) {

    int init_x = color == BLACK ? black_king_x : white_king_x;
    int init_y = color == BLACK ? black_king_y : white_king_y;

    string color_win = color == WHITE ? "Black" : "White";
    string color_err = color == BLACK ? "Black" : "White";

    // if check, we try to move the king
    if (is_check(color)) {

        if (chess_tab[init_x][init_y] != nullptr) {

            // test if the piece can move
            for (int i = 0; i < 8; i++) {

                for (int j = 0; j < 8; j++) {

                    if (get_piece(init_x, init_y)
                            ->is_valid_move(init_x, init_y, i, j,
                                            chess_tab) == GOOD) {

                        Piece *copy_piece = chess_tab[i][j];

                        // move the piece
                        chess_tab[i][j] = chess_tab[init_x][init_y];
                        chess_tab[init_x][init_y] = nullptr;

                        // if the check is not set, it is not
                        // checkmate
                        if (is_check(color) == false) {

                            // we go back to previous set
                            chess_tab[init_x][init_y] =
                                chess_tab[i][j];
                            chess_tab[i][j] = copy_piece;
                            return false;
                        }

                        chess_tab[init_x][init_y] = chess_tab[i][j];
                        chess_tab[i][j] = copy_piece;
                    }
                }
            }

            // if any move leads to a check, the king is checkmate
            cout << GRN "Checkmate! " << endl;
            cout << GRN << color_win << " player won !" NC << endl;
            return true;
        }

        // the king is not in the board, end the game
        cout << RED << color_err
             << " king is not on the board ! Please, reset the "
                "game. " NC
             << endl;
        return true;
    }

    return false;
}

bool Chessboard::is_stalemate(Color color) {

    string color_win = color == WHITE ? "Black" : "White";

    // test if the piece can move
    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++) {

            for (int k = 0; k < 8; k++) {

                for (int l = 0; l < 8; l++) {

                    if (chess_tab[i][j] != nullptr &&
                        chess_tab[i][j]->get_color() == color &&
                        chess_tab[i][j]->is_valid_move(
                            i, j, k, l, chess_tab) != ERROR) {

                        return false;
                    }
                }
            }
        }
    }

    // if no move can be done, the game is stalemate
    cout << GRN "Stalemate! " << endl;
    cout << GRN << color_win << " player won !" NC << endl;
    return true;
}

bool Chessboard::allowed_move(Color color, int init_x, int init_y,
                              int dest_x, int dest_y) {

    // security
    if (chess_tab[init_x][init_y] == nullptr)
        return false;

    int valid = 0;

    // white pawn
    if (chess_tab[init_x][init_y]->get_name() == "\u265F") {

        if (get_piece(init_x, init_y)
                ->is_valid_move(init_x, init_y, dest_x, dest_y,
                                chess_tab) == ONE_CASE_WHITE)
            valid = 1;

        if (get_piece(init_x, init_y)
                ->is_valid_move(init_x, init_y, dest_x, dest_y,
                                chess_tab) == TWO_CASE_WHITE)
            valid = 1;

        if (get_piece(init_x, init_y)
                ->is_valid_move(init_x, init_y, dest_x, dest_y,
                                chess_tab) == DIAGONAL_WHITE) {

            valid = 1;
        }
    } else if (chess_tab[init_x][init_y]->get_name() == "\u2659") {

        if (get_piece(init_x, init_y)
                ->is_valid_move(init_x, init_y, dest_x, dest_y,
                                chess_tab) == ONE_CASE_BLACK)
            valid = 1;

        if (get_piece(init_x, init_y)
                ->is_valid_move(init_x, init_y, dest_x, dest_y,
                                chess_tab) == TWO_CASE_BLACK)
            valid = 1;

        if (get_piece(init_x, init_y)
                ->is_valid_move(init_x, init_y, dest_x, dest_y,
                                chess_tab) == DIAGONAL_BLACK) {

            valid = 1;
        }
    } else {

        if (get_piece(init_x, init_y)
                ->is_valid_move(init_x, init_y, dest_x, dest_y,
                                chess_tab) == GOOD)
            valid = 1;
    }

    if (valid == 0)
        return false;

    Piece *copy_piece = chess_tab[dest_x][dest_y];

    // move the piece
    chess_tab[dest_x][dest_y] = chess_tab[init_x][init_y];
    chess_tab[init_x][init_y] = nullptr;

    // if the check is not set, it is an allowed move
    if (is_check(color) == false) {

        // we go back to previous set
        chess_tab[init_x][init_y] = chess_tab[dest_x][dest_y];
        chess_tab[dest_x][dest_y] = copy_piece;
        return true;
    }

    // we go back to previous set
    chess_tab[init_x][init_y] = chess_tab[dest_x][dest_y];
    chess_tab[dest_x][dest_y] = copy_piece;

    cout << RED "You are in check situation with this move" NC
         << endl;
    return false;
}

string Chessboard::canonical_position() const {

    string output;

    for (int i = 0; i <= 8; i++) {

        for (int j = 0; j <= 8; j++) {

            if (chess_tab[i][j] != nullptr) {

                string name = chess_tab[i][j]->get_name();
                Color color_pawn = chess_tab[i][j]->get_color();

                output += pgn_piece_name(name, color_pawn);
            } else
                output += "";

            output += ",";
        }
    }
    return output;
}

string Chessboard::pgn_piece_name(string const name,
                                  Color color) const {

    string psymb = "";

    if (name == "\u2656" || name == "\u265C")
        psymb = "R"; // Rook W
    else if (name == "\u2658" || name == "\u265E")
        psymb = "N"; // Knight W
    else if (name == "\u2657" || name == "\u265D")
        psymb = "B"; // Bishop W
    else if (name == "\u2655" || name == "\u265B")
        psymb = "Q"; // Queen W
    else if (name == "\u2654" || name == "\u265A")
        psymb = "K"; // King W
    else if (name == "\u2659" || name == "\u265F")
        psymb = "P"; // Pawn W

    if (psymb.size() > 0) {
        // one of the black piece has been found
        if (color == BLACK)
            return "b" + psymb;
        else if (color == WHITE)
            return "w" + psymb;
    }

    return psymb;
}