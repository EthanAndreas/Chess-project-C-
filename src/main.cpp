#include <iostream>

#include "game.h"

int main() {

    cout << "Begin of the game !" << endl;

    Game game = Game();
    game.print();

    bool end = false;

    while (end == false)
        end = game.stroke();
}