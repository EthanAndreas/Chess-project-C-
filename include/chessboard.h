#ifndef CHESSBOARD
#define CHESSBOARD

#include "piece.h"
#include <iostream>

class Chessboard {

  private:
    Piece *chess_tab[8][8];

  public:
    Chessboard();
    ~Chessboard();

    void print_board();
};

#endif