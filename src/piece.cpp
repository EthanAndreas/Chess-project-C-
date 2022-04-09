#include "piece.h"

Piece::Piece(Color col, string str) : color(col), name(str) {}

Piece::~Piece() {}

void Piece::print() { cout << name; }

Color Piece::get_color() const { return color; }
string Piece::get_name() const { return name; }