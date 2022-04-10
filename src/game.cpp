#include "game.h"

bool selection(string const &cmd) {
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd, mouvmtpattern);
}

bool kingside_castling_selection(string const &cmd) {
    regex mouvmtpattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd, mouvmtpattern);
}

bool queenside_castling_selection(string const &cmd) {
    regex mouvmtpattern("(O|o|0)-(O|o|0)-(O|o|0)");
    return regex_match(cmd, mouvmtpattern);
}

Game::Game() : chessboard(), player(WHITE) { *state = NONE; }

Game::~Game() { cout << endl << " End of game !" << endl; }

void Game::print() { chessboard.print_board(); }

State Game::get_state() const { return *state; }

void Game::set_state(State new_state) const {

    if (new_state == NONE)
        *state = NONE;
    else if (new_state == CHECK)
        *state = CHECK;
    else if (new_state == CHECKMATE)
        *state = CHECKMATE;
}

State Game::checkmate() {

    for (int init_x = 0; init_x < 8; init_x++) {

        for (int init_y = 0; init_y < 8; init_y++) {

            if (chessboard.get_piece(init_x, init_y) != nullptr &&
                chessboard.get_piece(init_x, init_y)->get_color() ==
                    player) {

                for (int dest_x = 0; dest_x < 8; dest_x++) {

                    for (int dest_y = 0; dest_y < 8; dest_y++) {

                        // if there is a case where we do not set a
                        // check situation, there is no checkmate
                        if (chessboard.allowed_move(player, init_x,
                                                    init_y, dest_x,
                                                    dest_y) == true)
                            return (*state = NONE);
                    }
                }
            }
        }
    }

    // in the case where we cannot only move any piece or any piece
    // that remove the check situation
    return (*state = CHECKMATE);
}

bool Game::kingside_castling() {

    int line;

    if (player == WHITE)
        line = 0;
    else
        line = 7;

    if (chessboard.get_piece(line, 4) != nullptr &&
        chessboard.get_piece(line, 4)->get_castling() != true &&
        chessboard.get_piece(line, 7) != nullptr &&
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

    if (chessboard.get_piece(line, 4) != nullptr &&
        chessboard.get_piece(line, 4)->get_castling() != true &&
        chessboard.get_piece(line, 0) != nullptr &&
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

    if (chessboard.get_piece(init_x, init_y) != nullptr &&
        chessboard.get_piece(init_x, init_y)->get_color() == player) {

        if (chessboard.allowed_move(player, init_x, init_y, dest_x,
                                    dest_y) == true) {

            chessboard.move(init_x, init_y, dest_x, dest_y);

            if (player == WHITE) {
                if (chessboard.is_check(BLACK) == true) {

                    set_state(CHECK);
                    cout << "Check's situation for black pawns !"
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
                    cout << "Check's situation for white pawns !"
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
                    "position."
                 << "Please try again." << endl;
            return false;
        }

        cout << "This is a forbidden move !"
             << "Please try again." << endl;
        return false;
    }

    cout << "You try to move a pawn that is not yours !"
         << "Please try again." << endl;
    return false;
}

bool Game::stroke() {

    cout << "Player ";
    if (player == white)
        cout << "white" << endl;
    if (player == BLACK)
        cout << "black" << endl;

    if (get_state() == CHECKMATE) {

        if (checkmate() == CHECKMATE) {

            cout << "Checkmate !" << endl;
            return true;
        }
    }

    if (checkmate() == CHECKMATE) {
        cout << "Checkmate !" << endl;
        return true;
    }

    int done = 0;

    while (done == 0) {

        string str;
        cout << "What is your stroke : ";
        cin >> str;

        if (str == "/quit")
            return true;

        if (kingside_castling_selection(str)) {

            if (kingside_castling() == true) {
                done = 1;
                cout << "Castling done !" << endl;
                break;
            }
        }

        else if (queenside_castling_selection(str)) {

            if (queenside_castling() = true) {
                done = 1;
                cout << "Castling done !" << endl;
                break;
            }
        }

        else if (selection(str)) {
            vector<int> coords = string_to_coord(reponse);

            if (deplacer(coords[0], coords[1], coords[2], coords[3]))
                coup_fait = true;
        }

        else {
            cout << endl << endl;
            cerr << "/!\\ La saisie est incorrecte. Réessayez."
                 << endl;
        }

        echiquier.afficher();
    }

    if (Jcouleur == Noir)
        Jcouleur = Blanc;
    else
        Jcouleur = Noir;

    return false;
}