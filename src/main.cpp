#include <iostream>

#include "game.h"

int main() {

    Chessboard chess;
    chess.print_board();

    cout << "Begin of the game !";

    Game game = Game();
    game.print();

    bool end = false;

    while (end == false) {

        end = game.stroke();
        game.print();
    }
}