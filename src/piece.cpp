#include "piece.h"

Piece::Piece(Color col, string str) : color(col), name(str) {}

Piece::~Piece() {}

void Piece::print() { cout << name; }

Color Piece::get_color() const { return color; }
string Piece::get_name() const { return name; }

bool Piece::is_valid_move(int init_x, int init_y, int dest_x,
                          int dest_y, Piece *chess_tab[8][8]) const {
    return false;
}