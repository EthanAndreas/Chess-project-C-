#include "game.h"

bool selection(string const &cmd) {
    // regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    // return regex_match(cmd, mouvmtpattern);
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

Game::Game() : chessboard(), player(WHITE) { state = NONE; }

Game::~Game() { cout << endl << "End of game !" << endl; }

void Game::print() { chessboard.print_board(); }

int *Game::string_to_int(string str) {

    if (str.empty() == true)
        return nullptr;

    int *tab = new int[4];

    // use of coord in the opposite order
    tab[1] = str[0] - 'a';
    tab[0] = str[1] - '0';
    tab[3] = str[3] - 'a';
    tab[2] = str[4] - '0';

    tab[1] -= 1;
    tab[3] -= 1;

    return tab;
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
        line = 0;
    else
        line = 7;

    if (chessboard.get_piece(line, 4) == nullptr)
        return false;

    if (chessboard.get_piece(line, 7) == nullptr)
        return false;

    if (chessboard.get_piece(line, 4)->get_castling() != true &&
        chessboard.get_piece(line, 7)->get_castling() != true) {

        if (chessboard.get_piece(line, 1) != nullptr ||
            chessboard.get_piece(line, 2) != nullptr) {

            cout << "Castling impossile !" << endl;
            return false;
        }
    }

    chessboard.move(line, 4, line, 6);
    chessboard.move(line, 7, line, 5);

    return true;
}

bool Game::queenside_castling() {

    int line;

    if (player == WHITE)
        line = 0;
    else
        line = 7;

    if (chessboard.get_piece(line, 4) == nullptr)
        return false;

    if (chessboard.get_piece(line, 0) == nullptr)
        return false;

    if (chessboard.get_piece(line, 4)->get_castling() != true &&
        chessboard.get_piece(line, 0)->get_castling() != true) {

        if (chessboard.get_piece(line, 3) != nullptr ||
            chessboard.get_piece(line, 5) != nullptr ||
            chessboard.get_piece(line, 6) != nullptr) {

            cout << "Castling impossile !" << endl;
            return false;
        }
    }

    chessboard.move(line, 4, line, 2);
    chessboard.move(line, 0, line, 3);

    return true;
}

bool Game::move(int init_x, int init_y, int dest_x, int dest_y) {

    if (chessboard.get_piece(init_x, init_y) == nullptr)
        return false;

    if (chessboard.get_piece(init_x, init_y)->get_color() == player) {

        if (chessboard.allowed_move(player, init_x, init_y, dest_x,
                                    dest_y) == true) {

            chessboard.move(init_x, init_y, dest_x, dest_y);

            if (player == WHITE) {
                if (chessboard.is_check(BLACK) == true) {

                    set_state(CHECK);
                    cout << "Check's situation against black pawns !"
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
                    cout << "Check's situation against white pawns !"
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

            cout << "There is already one of your pawns on this "
                    "position. "
                 << "Please try again." << endl;
            return false;
        }

        cout << "This is a forbidden move ! "
             << "Please try again." << endl;
        return false;
    }

    cout << "You try to move a pawn that is not yours ! "
         << "Please try again." << endl;
    return false;
}

bool Game::stroke() {

    if (player == WHITE)
        cout << "Player white" << endl;
    if (player == BLACK)
        cout << "Player black" << endl;

    checkmate();

    if (get_state() == CHECKMATE) {

        cout << "Checkmate !" << endl;
        return true;
    }

    bool done = false;

    while (done == false) {

        string str;
        cout << "What is your stroke : ";
        cin >> str;

        if (str == "/quit")
            return true;

        if (kingside_castling_selection(str)) {

            if (kingside_castling() == true) {
                done = false;
                cout << "Castling done !" << endl;
                break;
            }
        } else if (queenside_castling_selection(str)) {

            if (queenside_castling() == true) {
                done = false;
                cout << "Castling done !" << endl;
                break;
            }
        }

        int error = 0;

        if (selection(str) && error == 0) {

            int *coord = string_to_int(str);

            if (coord == nullptr)
                error = 1;
            else {

                if (move(coord[0], coord[1], coord[2], coord[3])) {
                    done = true;
                    break;
                }
            }
        } else {
            cout << "Error in command line !"
                    "Please try again."
                 << endl;
        }

        chessboard.print_board();
    }

    if (player == WHITE)
        player = BLACK;
    else
        player = WHITE;

    return false;
}