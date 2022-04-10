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
    State *state;

  public:
    Game();

    ~Game();

    bool stroke();

    // string to int (coordinates)
    static vector<int> stoi(string s);

    bool move(int ox, int oy, int dx, int dy);

    void print();

    State get_state() const;
    State set_state_check(bool check) const;
    State pat_or_mat();

    bool kingside_castling();
    bool queenside_castling();
};

#endif