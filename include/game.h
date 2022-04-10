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
    int state;

  public:
    Game();

    ~Game();

    bool stroke();

    // string to int (coordinates)
    static vector<int> stoi(string s);

    bool move(int ox, int oy, int dx, int dy);

    void print();

    int get_state() const;
    int set_state(bool check) const;
    bool pat_or_mat();

    bool kingside_castling();

    bool queenside_castling();
};

#endif