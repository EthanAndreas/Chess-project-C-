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

    for (int i = 0; i < 12; i++)
        destroyed_pieces[i] = 0;
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

int Chessboard::is_contained(string name) {

    // count the number of pieces with the name "name" on the board
    int nb = 0;

    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++) {

            if (chess_tab[i][j] != nullptr) {

                if (chess_tab[i][j]->get_name() == name)
                    nb++;
            }
        }
    }

    // if nb = 0, the piece is not on the board
    return nb;
}

bool Chessboard::lack_of_piece_for_checkmate(void) {

    // if a queen or a pawn or a rook is on the board, we can have a
    // checkmate
    if (is_contained("\u2656") == 0 && is_contained("\u265C") == 0 &&
        is_contained("\u2655") == 0 && is_contained("\u265B") == 0 &&
        is_contained("\u2659") == 0 && is_contained("\u265F") == 0) {

        if (is_contained("\u2654") != 0 &&
            is_contained("\u265A") != 0) {

            // king against king situation
            if (is_contained("\u2658") == 0 &&
                is_contained("\u265E") == 0 &&
                is_contained("\u2657") == 0 &&
                is_contained("\u265D") == 0)
                return true;

            // king against king and two knights situation
            if (is_contained("\u2658") == 0 &&
                is_contained("\u265E") == 2 &&
                is_contained("\u2657") == 0 &&
                is_contained("\u265D") == 0)
                return true;

            // king and two knights against king situation
            if (is_contained("\u2658") == 2 &&
                is_contained("\u265E") == 0 &&
                is_contained("\u2657") == 0 &&
                is_contained("\u265D") == 0)
                return true;

            // king against king and a bishop or a knight situation
            if (is_contained("\u2658") == 0 &&
                is_contained("\u2657") == 0) {

                if (is_contained("\u265E") == 1 ||
                    is_contained("\u265D") == 1)
                    return true;
            }

            // king and a bishop or a knight against king situation
            if (is_contained("\u265E") == 0 &&
                is_contained("\u265D") == 0) {

                if (is_contained("\u2658") == 1 ||
                    is_contained("\u2657") == 1)
                    return true;
            }
        }
    }

    return false;
}

void Chessboard::set_destroyed_pieces(string name) {

    // black rook
    if (name == "\u2656")
        destroyed_pieces[0]++;
    // white rook
    else if (name == "\u265C")
        destroyed_pieces[1]++;
    // black queen
    else if (name == "\u2655")
        destroyed_pieces[2]++;
    // white queen
    else if (name == "\u265B")
        destroyed_pieces[3]++;
    // black pawn
    else if (name == "\u2659")
        destroyed_pieces[4]++;
    // white pawn
    else if (name == "\u265F")
        destroyed_pieces[5]++;
    // black king
    else if (name == "\u2654")
        destroyed_pieces[6]++;
    // white king
    else if (name == "\u265A")
        destroyed_pieces[7]++;
    // black knight
    else if (name == "\u2658")
        destroyed_pieces[8]++;
    // white knight
    else if (name == "\u265E")
        destroyed_pieces[9]++;
    // black bishop
    else if (name == "\u2657")
        destroyed_pieces[10]++;
    // white bishop
    else if (name == "\u265D")
        destroyed_pieces[11]++;
}

void Chessboard::move(int init_x, int init_y, int dest_x,
                      int dest_y) {

    // security
    if (chess_tab[init_x][init_y] == nullptr)
        return;

    // in the case where the player destroy an opponent piece
    if (chess_tab[dest_x][dest_y] != nullptr) {

        stroke_without_take = 0;
        set_destroyed_pieces(chess_tab[dest_x][dest_y]->get_name());
        delete chess_tab[dest_x][dest_y];
    } else
        // if the player does not do a take
        set_counter();

    // if the player moves a pawn the counter is put to 0
    if ((chess_tab[init_x][init_y]->get_name() == "\u2659" ||
         chess_tab[init_x][init_y]->get_name() == "\u265F"))
        stroke_without_take = 0;

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

    // management of pawn's promotion
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

    // test if color's king is in check
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

    // display
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

                            // if a move is possible without
                            // creating a check situation, then
                            // there is no checkamte
                            if (allowed_move(color, k, l, i, j) ==
                                true)
                                return false;
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

    // check if we can checkmate the opponent
    if (lack_of_piece_for_checkmate() == true) {

        cout << endl << GRN "The game is a draw !" NC << endl;
        return true;
    }

    // display
    string color_win = color == WHITE ? "Black" : "White";

    // test if the piece can move
    for (int k = 0; k < 8; k++) {
        for (int l = 0; l < 8; l++) {

            if (chess_tab[k][l] != nullptr &&
                chess_tab[k][l]->get_color() == color) {

                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {

                        // if a move is possible without creating a
                        // check situation, then there is no stalemate
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

void Chessboard::print_destroyed_pieces(void) {

    cout << endl;

    // black rook
    cout << "\u2656"
         << " " << destroyed_pieces[0];
    cout << " ";
    // black queen
    cout << "\u2655"
         << " " << destroyed_pieces[2];
    cout << " ";
    // black pawn
    cout << "\u2659"
         << " " << destroyed_pieces[4];
    cout << " ";
    // black king
    cout << "\u2654"
         << " " << destroyed_pieces[6];
    cout << " ";
    // black knight
    cout << "\u2658"
         << " " << destroyed_pieces[8];
    cout << " ";
    // black bishop
    cout << "\u2657"
         << " " << destroyed_pieces[10];
    cout << endl;

    // white rook
    cout << "\u265C"
         << " " << destroyed_pieces[1];
    cout << " ";
    // white queen
    cout << "\u265B"
         << " " << destroyed_pieces[3];
    cout << " ";
    // white pawn
    cout << "\u265F"
         << " " << destroyed_pieces[5];
    cout << " ";
    // white king
    cout << "\u265A"
         << " " << destroyed_pieces[7];
    cout << " ";
    // white knight
    cout << "\u265E"
         << " " << destroyed_pieces[9];
    cout << " ";
    // white bishop
    cout << "\u265D"
         << " " << destroyed_pieces[11];
    cout << endl;
}