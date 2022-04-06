#ifndef GAME
#define GAME

#include <vector>
#include <regex>

#include "chessboard.h"
using namespace std;

bool saisie_correcte(string const & cmd);
bool saisie_correcte_petitroque(string const & cmd);
bool saisie_correcte_grandroque(string const & cmd);

class Game{

    private :
        Chessboard chessboard;
        Color player;
        int state;
    
    public :
        //Constructeur
        Game();

        //Destructeur
        ~Game();

        bool stroke();

        static vector<int> stoi(string s);
        // string to int (coordinates)
        
        bool move(int ox, int oy, int dx, int dy);

        int get_state() const;

        void set_state(int st);

        bool pat_or_mat();

        bool kingside_castling();

        bool queenside_castling();
};

#endif