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

State Game::set_state_check(bool check) const {

    if (check == true)
        return (*state = CHECK);

    return (*state = NONE);
}

State Game::pat_or_mat() {

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