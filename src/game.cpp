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

Game::Game() : chessboard(), player(WHITE), state(NONE) {}

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

State Game::get_state() const { return state; }

void Game::set_state(State new_state) {

    if (new_state == NONE)
        state = NONE;
    else if (new_state == CHECK)
        state = CHECK;
    else if (new_state == CHECKMATE)
        state = CHECKMATE;
}

State Game::checkmate() {

    if (chessboard.is_checkmate(player)) {

        state = CHECKMATE;
        return CHECKMATE;
    } else {

        state = NONE;
        return NONE;
    }
}

bool Game::kingside_castling() {

    int line;

    if (player == WHITE)
        line = 7;
    else
        line = 0;

    if (chessboard.get_piece(line, 4) == nullptr) {

        cout << RED "There is no piece at the king's position !" NC
             << endl;
        return false;
    }

    if (chessboard.get_piece(line, 7) == nullptr) {

        cout << RED "There is no piece at the rook's position !" NC
             << endl;
        return false;
    }

    cout << "res castling" << endl;
    cout << chessboard.get_piece(line, 4)->get_castling() << endl;
    cout << chessboard.get_piece(line, 7)->get_castling() << endl;

    if (chessboard.get_piece(line, 4)->get_castling() == true) {

        cout << RED "The king has already moved !" NC << endl;
        return false;
    }

    if (chessboard.get_piece(line, 7)->get_castling() == true) {

        cout << RED "The rook has already moved !" NC << endl;
        return false;
    }

    if (chessboard.get_piece(line, 5) != nullptr ||
        chessboard.get_piece(line, 6) != nullptr) {

        cout << RED "Castling impossile !" NC << endl;
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

        cout << RED "There is no piece at the king's position !" NC
             << endl;
        return false;
    }

    if (chessboard.get_piece(line, 0) == nullptr) {

        cout << RED "There is no piece at the rook's position !" NC
             << endl;
        return false;
    }

    if (chessboard.get_piece(line, 4)->get_castling() == true) {

        cout << RED "The king has already moved !" NC << endl;
        return false;
    }

    if (chessboard.get_piece(line, 0)->get_castling() == true) {

        cout << RED "The rook has already moved !" NC << endl;
        return false;
    }

    if (chessboard.get_piece(line, 1) != nullptr ||
        chessboard.get_piece(line, 2) != nullptr ||
        chessboard.get_piece(line, 3) != nullptr) {

        cout << RED "Castling impossile !" NC << endl;
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

        cout << RED "No piece at this position !"
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

                    set_state(CHECK);
                    cout << NC
                        "Check's situation against black pawns !"
                         << endl;
                } else {

                    // if the check's situation is counter by the
                    // player, the state is set to NONE
                    if (get_state() == CHECK)
                        set_state(NONE);
                }
            }

            else if (player == BLACK) {

                if (chessboard.is_check(WHITE) == true) {

                    set_state(CHECK);
                    cout << NC
                        "Check's situation against white pawns !"
                         << endl;
                } else {

                    if (get_state() == CHECK)
                        set_state(NONE);
                }
            }

            return true;
        }

        if (chessboard.get_piece(dest_x, dest_y) != nullptr &&
            chessboard.get_piece(init_x, init_y)->get_color() ==
                chessboard.get_piece(dest_x, dest_y)->get_color()) {

            cout << RED "There is already one of your pawns on this "
                        "position. "
                 << "Please try again." NC << endl;
            return false;
        }

        cout << RED "This is a forbidden move ! "
             << "Please try again." NC << endl;
        return false;
    }

    cout << RED "You try to move a pawn that is not yours ! "
         << "Please try again." NC << endl;
    return false;
}

bool Game::stroke() {

    if (player == WHITE)
        cout << endl << NC "White player's round" << endl;
    if (player == BLACK)
        cout << endl << NC "Black player's round" << endl;

    checkmate();

    if (get_state() == CHECKMATE) {

        cout << GRN "Checkmate !" NC << endl;
        return true;
    }

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
            cout << RED "Error in command line ! "
                        "Please try again." NC
                 << endl;
        }
    }

    chessboard.print_board();

    player = (player == WHITE) ? BLACK : WHITE;

    return false;
}