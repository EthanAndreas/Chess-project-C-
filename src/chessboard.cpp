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

    // save of king's location
    white_king_x = 7;
    white_king_y = 4;
    black_king_x = 0;
    black_king_y = 4;

    stroke_without_take = 0;
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

    // in the case where the player destroy an opponent piece
    if (chess_tab[dest_x][dest_y] != nullptr) {

        stroke_without_take = 0;
        delete chess_tab[dest_x][dest_y];
    } else
        set_counter();

    // save that the piece has move at least once
    chess_tab[init_x][init_y]->set_castling();

    // if the piece moved is a king, update the king's location
    if (chess_tab[init_x][init_y]->get_name() == "\u2654") {

        black_king_x = dest_x;
        black_king_y = dest_y;
    } else if (chess_tab[init_x][init_y]->get_name() == "\u265A") {

        white_king_x = dest_x;
        white_king_y = dest_y;
    }

    // move the piece
    chess_tab[dest_x][dest_y] = chess_tab[init_x][init_y];
    chess_tab[init_x][init_y] = nullptr;

    if (chess_tab[dest_x][dest_y]->get_name() == "\u265F") {

        if (dest_x == 0)
            chess_tab[dest_x][dest_y]->promotion(
                dest_x, dest_y, chess_tab,
                chess_tab[dest_x][dest_y]->get_color());

    } else if (chess_tab[dest_x][dest_y]->get_name() == "\u2659") {

        if (dest_x == 7)
            chess_tab[dest_x][dest_y]->promotion(
                dest_x, dest_y, chess_tab,
                chess_tab[dest_x][dest_y]->get_color());
    }
}

bool Chessboard::is_check(Color color) {
    // test if color's pawns are in check

    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++) {

            if (chess_tab[i][j] != nullptr &&
                chess_tab[i][j]->get_color() != color) {

                if (color == BLACK) {

                    // we try if all other pieces can touch the
                    // king
                    if (get_piece(i, j)->is_valid_move(
                            i, j, black_king_x, black_king_y,
                            chess_tab) == true)
                        return true;
                } else {

                    // we try if all other pieces can touch the
                    // king
                    if (get_piece(i, j)->is_valid_move(
                            i, j, white_king_x, white_king_y,
                            chess_tab) == true)
                        return true;
                }
            }
        }
    }

    return false;
}

bool Chessboard::is_checkmate(Color color) {

    string color_win = color == WHITE ? "Black" : "White";
    string color_err = color == BLACK ? "Black" : "White";

    int init_x = color == BLACK ? black_king_x : white_king_x;
    int init_y = color == BLACK ? black_king_y : white_king_y;

    if (chess_tab[init_x][init_y] == nullptr) {

        // the king is not in the board, end the game
        cerr << RED << color_err
             << " king is not on the board ! Please, reset the "
                "game. " NC
             << endl;
        return true;
    }

    // if check, we search a move that turns off the check's
    // situation
    if (is_check(color)) {

        // every piece available
        for (int k = 0; k < 8; k++) {
            for (int l = 0; l < 8; l++) {

                if (chess_tab[k][l] != nullptr &&
                    chess_tab[k][l]->get_color() == color) {

                    // test every possible move of the piece
                    for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < 8; j++) {

                            // if the move is correct
                            if (chess_tab[i][j] == nullptr ||
                                (chess_tab[i][j] != nullptr &&
                                 chess_tab[i][j]->get_color() !=
                                     color)) {

                                if (allowed_move(color, k, l, i, j) ==
                                    true)
                                    return false;
                            }
                        }
                    }
                }
            }
        }

        // if any move leads to a check, the king is checkmate
        cout << endl << GRN "Checkmate ! " << endl;
        cout << GRN << color_win << " player won !" NC << endl;
        return true;
    }

    return false;
}

void Chessboard::set_counter(void) { stroke_without_take++; }

bool Chessboard::is_stalemate(Color color) {

    // check if the game is a draw, which it signicates that 50
    // strokes without a take was done
    if (stroke_without_take == 50) {

        cout << endl << GRN "The game is a draw !" NC << endl;
        return true;
    }

    string color_win = color == WHITE ? "Black" : "White";

    // test if the piece can move
    for (int k = 0; k < 8; k++) {
        for (int l = 0; l < 8; l++) {

            if (chess_tab[k][l] != nullptr &&
                chess_tab[k][l]->get_color() == color) {

                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {

                        if (allowed_move(color, k, l, i, j) == true)
                            return false;
                    }
                }
            }
        }
    }

    // if no move can be done, the game is stalemate
    cout << endl << GRN "Stalemate ! " << endl;
    cout << GRN << color_win << " player won !" NC << endl;
    return true;
}

bool Chessboard::allowed_move(Color color, int init_x, int init_y,
                              int dest_x, int dest_y) {

    // security
    if (chess_tab[init_x][init_y] == nullptr)
        return false;

    int valid = 0;

    if (get_piece(init_x, init_y)
            ->is_valid_move(init_x, init_y, dest_x, dest_y,
                            chess_tab) == true)
        valid = 1;

    if (valid == 0)
        return false;

    if (chess_tab[dest_x][dest_y] != nullptr) {

        if (chess_tab[dest_x][dest_y]->get_color() == color)
            return false;
    }

    Piece *copy_piece = chess_tab[dest_x][dest_y];

    // if the piece we move is a king, update the location of the
    // king
    if (chess_tab[init_x][init_y]->get_name() == "\u2654") {

        black_king_x = dest_x;
        black_king_y = dest_y;
    } else if (chess_tab[init_x][init_y]->get_name() == "\u265A") {

        white_king_x = dest_x;
        white_king_y = dest_y;
    }

    // move the piece
    chess_tab[dest_x][dest_y] = chess_tab[init_x][init_y];
    chess_tab[init_x][init_y] = nullptr;

    // if the check is not set, it is an allowed move
    if (is_check(color) == false) {

        // we go back to previous king's location
        if (chess_tab[dest_x][dest_y]->get_name() == "\u2654") {

            black_king_x = init_x;
            black_king_y = init_y;
        } else if (chess_tab[dest_x][dest_y]->get_name() ==
                   "\u265A") {

            white_king_x = init_x;
            white_king_y = init_y;
        }

        // we go back to previous set
        chess_tab[init_x][init_y] = chess_tab[dest_x][dest_y];
        chess_tab[dest_x][dest_y] = copy_piece;
        return true;
    }

    // we go back to previous king's location
    if (chess_tab[dest_x][dest_y]->get_name() == "\u2654") {

        black_king_x = init_x;
        black_king_y = init_y;
    } else if (chess_tab[dest_x][dest_y]->get_name() == "\u265A") {

        white_king_x = init_x;
        white_king_y = init_y;
    }

    // we go back to previous set
    chess_tab[init_x][init_y] = chess_tab[dest_x][dest_y];
    chess_tab[dest_x][dest_y] = copy_piece;

    return false;
}