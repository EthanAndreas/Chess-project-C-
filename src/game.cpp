#include "game.h"

bool selection(string const &cmd) {
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd, mouvmtpattern);
    return true;
}

bool kingside_castling_selection(string const &cmd) {
    regex mouvmtpattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd, mouvmtpattern);
}

bool queenside_castling_selection(string const &cmd) {
    regex mouvmtpattern("(O|o|0)-(O|o|0)-(O|o|0)");
    return regex_match(cmd, mouvmtpattern);
}

Game::Game() : chessboard(), player(BLACK) {}

Game::~Game() { cout << endl << GRN "End of game !" NC << endl; }

void Game::print() { chessboard.print_board(); }

// string to coordinates
int *Game::string_to_coord(string str) {

    int *coord = new int[2];
    coord[1] = str[0] - 'a';
    coord[0] = str[1] - '1';
    coord[3] = str[2] - 'a';
    coord[2] = str[3] - '1';

    return coord;
}

bool Game::checkmate() {

    if (chessboard.is_checkmate(player) == true ||
        chessboard.is_stalemate(player) == true)
        return true;
    else
        return false;
}

bool Game::kingside_castling() {

    int line;

    if (player == WHITE)
        line = 7;
    else
        line = 0;

    if (chessboard.get_piece(line, 4) == nullptr) {

        cerr << RED "There is no piece at the king's position !" NC
             << endl;
        return false;
    }

    if (chessboard.get_piece(line, 7) == nullptr) {

        cerr << RED "There is no piece at the rook's position !" NC
             << endl;
        return false;
    }

    if (chessboard.get_piece(line, 4)->get_castling() == true) {

        cerr << RED "The king has already moved !" NC << endl;
        return false;
    }

    if (chessboard.get_piece(line, 7)->get_castling() == true) {

        cerr << RED "The rook has already moved !" NC << endl;
        return false;
    }

    if (chessboard.get_piece(line, 5) != nullptr ||
        chessboard.get_piece(line, 6) != nullptr) {

        cerr << RED "Castling impossile !" NC << endl;
        return false;
    }

    chessboard.get_piece(line, 4)->set_castling();
    chessboard.get_piece(line, 7)->set_castling();
    chessboard.move(line, 4, line, 6);
    chessboard.move(line, 7, line, 5);

    return true;
}

bool Game::queenside_castling() {

    int line;

    if (player == WHITE)
        line = 7;
    else
        line = 0;

    if (chessboard.get_piece(line, 4) == nullptr) {

        cerr << RED "There is no piece at the king's position !" NC
             << endl;
        return false;
    }

    if (chessboard.get_piece(line, 0) == nullptr) {

        cerr << RED "There is no piece at the rook's position !" NC
             << endl;
        return false;
    }

    if (chessboard.get_piece(line, 4)->get_castling() == true) {

        cerr << RED "The king has already moved !" NC << endl;
        return false;
    }

    if (chessboard.get_piece(line, 0)->get_castling() == true) {

        cerr << RED "The rook has already moved !" NC << endl;
        return false;
    }

    if (chessboard.get_piece(line, 1) != nullptr ||
        chessboard.get_piece(line, 2) != nullptr ||
        chessboard.get_piece(line, 3) != nullptr) {

        cerr << RED "Castling impossile !" NC << endl;
        return false;
    }

    chessboard.get_piece(line, 4)->set_castling();
    chessboard.get_piece(line, 0)->set_castling();
    chessboard.move(line, 4, line, 2);
    chessboard.move(line, 0, line, 3);

    return true;
}

bool Game::move(int init_x, int init_y, int dest_x, int dest_y) {

    if (chessboard.get_piece(init_x, init_y) == nullptr) {

        cerr << RED "No piece at this position !"
                    " Please, try again." NC
             << endl;
        return false;
    }

    if (chessboard.get_piece(init_x, init_y)->get_color() == player) {

        if (chessboard.allowed_move(player, init_x, init_y, dest_x,
                                    dest_y) == true) {

            chessboard.move(init_x, init_y, dest_x, dest_y);

            if (player == WHITE) {
                if (chessboard.is_check(BLACK) == true) {

                    cout << NC
                        "Check's situation against black pawns !"
                         << endl;
                }
            }

            else if (player == BLACK) {

                if (chessboard.is_check(WHITE) == true) {

                    cout << NC
                        "Check's situation against white pawns !"
                         << endl;
                }
            }

            return true;
        }

        if (chessboard.get_piece(dest_x, dest_y) != nullptr &&
            chessboard.get_piece(init_x, init_y)->get_color() ==
                chessboard.get_piece(dest_x, dest_y)->get_color()) {

            cerr << RED "There is already one of your pawns on this "
                        "position. "
                 << "Please try again." NC << endl;
            return false;
        }

        cerr << RED "This is a forbidden move ! "
             << "Please try again." NC << endl;
        return false;
    }

    cerr << RED "You try to move a pawn that is not yours ! "
         << "Please try again." NC << endl;
    return false;
}

bool Game::stroke() {

    // check the check's situation each stroke, display in function :
    // Chessboard::is_checkmate
    if (checkmate() == true)
        return true;

    if (player == WHITE)
        cout << endl << GRN "White player's round" NC << endl;
    if (player == BLACK)
        cout << endl << GRN "Black player's round" NC << endl;

    // loop for the stroke until the player choose a valid move
    bool done = false;
    while (done == false) {

        string str;
        cout << NC "What is your stroke : ";
        cin >> str;

        if (str == "/quit")
            return true;

        if (kingside_castling_selection(str)) {

            if (kingside_castling() == true) {
                done = false;
                cout << GRN "Castling done !" NC << endl;
                break;
            }
        } else if (queenside_castling_selection(str)) {

            if (queenside_castling() == true) {
                done = false;
                cout << GRN "Castling done !" NC << endl;
                break;
            }
        } else if (selection(str)) {

            int *coord = string_to_coord(str);

            if (move(coord[0], coord[1], coord[2], coord[3])) {
                done = true;
                break;
            }

        } else {
            cerr << RED "Error in command line ! "
                        "Please try again." NC
                 << endl;
        }
    }

    if (checkmate() == true)
        return true;

    chessboard.print_board();

    player = (player == WHITE) ? BLACK : WHITE;

    return false;
}

string Game::canonical_position() {

    string output;

    // reversed display because white pawns is on the top of the board
    for (int i = 7; i > -1; i--) {

        for (int j = 7; j > -1; j--) {

            if (chessboard.get_piece(i, j) != nullptr) {

                string name = chessboard.get_piece(i, j)->get_name();
                Color color_pawn =
                    chessboard.get_piece(i, j)->get_color();

                output += pgn_piece_name(name, color_pawn);
            } else
                output += "";

            output += ",";
        }
    }
    return output;
}

string Game::pgn_piece_name(string name, Color color) {

    string psymb;

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
    else
        psymb = "";

    if (psymb.size() > 0) {
        // one of the black piece has been found
        if (color == BLACK)
            psymb = "b" + psymb;
        else if (color == WHITE)
            psymb = "w" + psymb;
    }

    return psymb;
}