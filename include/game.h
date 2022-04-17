#ifndef GAME
#define GAME

#include <regex>
#include <vector>

#include "chessboard.h"
using namespace std;

bool selection(string const &cmd);
bool kingside_castling_selection(string const &cmd);
bool queenside_castling_selection(string const &cmd);

class Game {

  private:
    Chessboard chessboard;
    Color player;

  public:
    Game();

    ~Game();

    void print();

    bool checkmate();

    bool kingside_castling();
    bool queenside_castling();

    int *string_to_coord(string str);

    bool move(int init_x, int init_y, int dest_x, int dest_y);
    bool stroke();

    string canonical_position();
    string pgn_piece_name(string const name, Color color);
};

#endif