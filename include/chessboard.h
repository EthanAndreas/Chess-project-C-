#ifndef CHESSBOARD
#define CHESSBOARD

#include "piece.h"
#include <iostream>

class Chessboard {

  private:
    Piece *chess_tab[8][8];
    int *white_king[2];
    int *black_king[2];

  public:
    Chessboard();
    ~Chessboard();

    void print_board();

    Piece *get_piece(int x, int y) const;

    void move(int init_x, int init_y, int dest_x, int dest_y);
    bool is_check(Color color);
    bool allowed_move(Color color, int init_x, int init_y, int dest_x, int dest_y);

    string canonical_position() const;
    string pgn_piece_name(string const name, bool view_pawn, bool view_color) const;

};

#endif