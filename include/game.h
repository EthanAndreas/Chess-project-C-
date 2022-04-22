#ifndef GAME
#define GAME

#include <regex>
#include <vector>

#include "chessboard.h"
using namespace std;

/**
 * @brief Check if the selection of coordinates by the user is valid
 * @param cmd
 * @return true
 * @return false
 */
bool selection(string const &cmd);

/**
 * @brief Check if the selection of coordinates for kingside castling
 * by the user is valid
 * @param cmd
 * @return true
 * @return false
 */
bool kingside_castling_selection(string const &cmd);

/**
 * @brief Check if the selection of coordinates for queenside castling
 * by the user is valid
 *
 * @param cmd
 * @return true
 * @return false
 */
bool queenside_castling_selection(string const &cmd);

/**
 * @brief Manage the stroke (the player's alternating, the end of the
 * game if there is a checkmate/stalemate), manage the movement chosen
 * by the user, manage the coordinates and the selection
 */
class Game {

  private:
    Chessboard chessboard;
    Color player;

  public:
    /**
     * @brief Construct a new Game object
     */
    Game();

    /**
     * @brief Destroy the Game object
     */
    ~Game();

    /**
     * @brief Print the chessboard
     */
    void print();

    /**
     * @brief Verify if one of the player is in checkmate
     */
    bool checkmate();

    /**
     * @brief Do the kingside castling
     */
    bool kingside_castling();

    /**
     * @brief Do the queenside castling
     */
    bool queenside_castling();

    /**
     * @brief Convert the string entered by the user in coordinates
     * @param cmd
     */
    int *string_to_coord(string str);

    /**
     * @brief Manage the movement chosen by the user
     *
     * @param init_x
     * @param init_y
     * @param dest_x
     * @param dest_y
     * @return true (if the move is done)
     * @return false (if the move is not done)
     */
    bool move(int init_x, int init_y, int dest_x, int dest_y);

    /**
     * @brief Manage the player's alternating, the stroke and the end
     * of the game
     * @return true (if the game is ended)
     * @return false (if the game is not ended)
     */
    bool stroke();

    /**
     * @brief Display the pawn on the chessboard at the end of the
     * game
     * @return string
     */
    string canonical_position();

    /**
     * @brief Convert the piece (Ex : "\u2656") in bR for black rook
     *
     * @param name (Ex : "\u2656")
     * @param color (Ex : BLACK)
     * @return string
     */
    string pgn_piece_name(string const name, Color color);
};

#endif