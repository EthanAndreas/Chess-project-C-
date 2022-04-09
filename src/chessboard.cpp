#include "chessboard.h"
#include "piece.h"
using namespace std;

Chessboard::Chessboard() {

    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++)
            chess_tab[i][j] = nullptr;
    }

    // Initialisation of pieces
    chess_tab[0][0] = new Rook(Color::WHITE, "\u2656");
    chess_tab[0][1] = new Knight(Color::WHITE, "\u2658");
    chess_tab[0][2] = new Bishop(Color::WHITE, "\u2657");
    chess_tab[0][3] = new Queen(Color::WHITE, "\u2655");
    chess_tab[0][4] = new King(Color::WHITE, "\u2654");
    chess_tab[0][5] = new Bishop(Color::WHITE, "\u2657");
    chess_tab[0][6] = new Knight(Color::WHITE, "\u2658");
    chess_tab[0][7] = new Rook(Color::WHITE, "\u2656");
    chess_tab[7][0] = new Rook(Color::BLACK, "\u265C");
    chess_tab[7][1] = new Knight(Color::BLACK, "\u265E");
    chess_tab[7][2] = new Bishop(Color::BLACK, "\u265D");
    chess_tab[7][3] = new Queen(Color::BLACK, "\u265B");
    chess_tab[7][4] = new King(Color::BLACK, "\u265A");
    chess_tab[7][5] = new Bishop(Color::BLACK, "\u265D");
    chess_tab[7][6] = new Knight(Color::BLACK, "\u265E");
    chess_tab[7][7] = new Rook(Color::BLACK, "\u265C");

    for (int i = 0; i < 8; i++) {
        chess_tab[1][i] = new Pawn(Color::WHITE, "\u2659");
        chess_tab[6][i] = new Pawn(Color::BLACK, "\u265F");
    }

    // save of king's location
    *white_king[0] = 0;
    *white_king[1] = 4;
    *black_king[0] = 7;
    *black_king[1] = 4;
}

Chessboard::~Chessboard() {

    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++) {

            if (chess_tab[i][j])
                delete chess_tab[i][j];
        }
    }
}

void Chessboard::print_board() {

    static const string &space = "     ";
    static const string &line =
        "  +-----+-----+-----+-----+-----+-----+-----+-----+";

    // print the column name
    cout << "     a     b     c     d     e     f     g     h    "
         << endl;
    cout << line << endl;

    for (int i = 7; i >= 0; i--) {

        // print the line number
        cout << i + 1 << " ";

        for (int j = 0; j < 8; j++) {

            // separator between column
            cout << "|";

            if (chess_tab[i][j] != nullptr) {

                cout << " ";
                chess_tab[i][j]->print();
                cout << "   ";

            } else
                cout << space;
        }

        cout << "|";
        cout << endl << line << endl;
    }
}


Piece *Chessboard::get_piece(int x, int y) const{ return chess_tab[x][y]; }

void Chessboard::move(int init_x, int init_y, int dest_x, int dest_y){

    // in the case where the player destrinit_y an opponent piece
    if(chess_tab[dest_x][dest_y] != nullptr)
        delete chess_tab[dest_x][dest_y];

    // if the pawn to move is a king, update the location's save
    if(chess_tab[init_x][init_y]->get_name() == "\u2654") {

        if (chess_tab[init_x][init_y]->get_color() == WHITE) {

            *white_king[0] = dest_x;
            *white_king[1] = dest_y;            
        } else {

            *black_king[0] = dest_x;
            *black_king[1] = dest_y;
        }
    }

    chess_tab[dest_x][dest_y] = chess_tab[init_x][init_y];
    chess_tab[init_x][init_y] = nullptr;
}


bool Chessboard::is_check(Color color){ 

    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++) {

            if (chess_tab[i][j] != nullptr && chess_tab[i][j]->get_color()!= color) {
                
                if(color == WHITE){

                    if (get_piece(i,j)->is_valid_move(i,j,*white_king[0],*white_king[1],chess_tab))
                        return true;
                } else {

                    if (get_piece(i,j)->is_valid_move(i,j,*black_king[0],*black_king[1],chess_tab))
                        return true;
                }
            }
        }
    }

    return false;
}


bool Chessboard::allowed_move(Color color, int init_x, int init_y, int dest_x, int dest_y){

    if ((get_piece(init_x,init_y)->is_valid_move(init_x,init_y,dest_x,dest_y,chess_tab)) == false)
        return false;

    Piece* copy_piece = chess_tab[dest_x][dest_y];

    // move the piece
    chess_tab[dest_x][dest_y] = chess_tab[init_x][init_y];
    chess_tab[init_x][init_y] = nullptr;

    // if the check is not set, it is an allowed move
    if (is_check(color) == false)
        return true;

    // if not, we go back to previous set
    chess_tab[init_x][init_y] = chess_tab[dest_x][dest_y];
    chess_tab[dest_x][dest_y] = copy_piece;

    return false;
}

string Chessboard::canonical_position() const {

      string output;
      for (size_t row(1); row<=8; row++){

              for (char col('a'); col <= 'h';col++) {

                    //   Square square(col + to_string(row)); 

                    //   if (!empty_set(square))
                              // get pieces with theit PGN names, 
                              // true -> with P for pawns, true -> w/b for colors.
                            //   output += pgn_piece_name(get_piece(square)->to_string(),true,true);
                      output += ",";
              }
      }
      return output;
}

string Chessboard::pgn_piece_name(string const name, bool view_pawn, bool view_color) const {

    string psymb;

    if      (name == "\u2656") 
        psymb ="R";  // Rook W
    else if (name == "\u2658") 
        psymb ="N";  // Knight W
    else if (name == "\u2657") 
        psymb ="B";  // Bishop W
    else if (name == "\u2655") 
        psymb ="Q";  // Queen W
    else if (name == "\u2654") 
        psymb ="K";  // King W
    else if (name.rfind("\u2659",0) == 0 && view_pawn) 
        psymb = "P"; // Pawn W

    if (psymb.size()>0) { 

        // one of the white piece has been found
        if (view_color)
            return "w" + psymb;
        else
            return psymb;
    } 

    if (name == "\u265C") 
        // Rook B
        psymb = "R"; 
    else if (name == "\u265E") 
        // Knight B
        psymb = "N";  
    else if (name == "\u265D") 
        // Bishop B
        psymb = "B"; 
    else if (name == "\u265B")  
        // Queen B
        psymb = "Q"; 
    else if (name == "\u265A")  
        // King B
        psymb = "K"; 
    else if (name.rfind("\u265F",0) == 0 && view_pawn) 
        // Pawn B
        psymb = "P"; 

    if (psymb.size()>0) { 
        // one of the black piece has been found
        if (view_color)
                return "b" + psymb;
        else
                return psymb;
    } else 
        return "";
}